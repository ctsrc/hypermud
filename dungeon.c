/*
 * ASCII Random Dungeon Generator
 *
 * Robert Nystrom
 * @munificentbob
 * for Ginny
 * 2008-2019
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Number of characters wide and high.
const int W = 80;
const int H = 40;

int map[40][80];

/*
 * Return a random integer in range [lower_bound_incl, upper_bound_excl).
 */
int rangedrand (int lower_bound_incl, int upper_bound_excl)
{
  return lower_bound_incl + (rand() % (upper_bound_excl - lower_bound_incl));
}

void cave (bool);

int main (int argc, const char *argv[])
{
  // Set seed for pseudo-random generator.
  if (argc == 1)
  {
    srand((int) time(NULL));
  }
  else if (argc == 2 && strcmp(argv[1], "--deterministic") == 0)
  {
    srand(0);
  }
  else
  {
    fprintf(stderr, "Invalid argument.\n");
    return EXIT_FAILURE;
  }

  // Initialize map to consist purely of blank spaces.
  for (int y = 0 ; y < H ; y++)
  {
    for (int x = 0 ; x < W ; x++)
    {
      map[y][x] = ' ';
    }
  }

  // Generate dungeon.
  for (int j = 0 ; j < 1000 ; j++)
  {
    cave(j == 0);
  }

  // Print generated dungeon.
  for (int y = 0 ; y < H ; y++)
  {
    for (int x = 0 ; x < W ; x++)
    {
      int c = map[y][x];

      putchar(c == '!' ? '#' : c);

      if (x == W - 1)
      {
        printf("\n");
      }
    }
  }

  return EXIT_SUCCESS;
}

void cave (bool first_cave)
{
  // Dimensions of cave floor are (w + 1) * (h + 1).
  int w = rangedrand(5, 15);
  int h = rangedrand(3, 9);

  // Top left cave wall corner is at coord (x, y) = (x0, y0).
  int x0 = rangedrand(0, ((W - 1) - w) - 1);
  int y0 = rangedrand(0, ((H - 1) - h) - 1);

  // Bottom right cave wall corner.
  int x1 = x0 + w + 2;
  int y1 = y0 + h + 2;

  // If there is a floor present already within
  // the bounds where we were going to create
  // a new cave then do not create a new cave here.
  for (int y = y0 ; y <= y1 ; y++)
  {
    for (int x = x0 ; x <= x1 ; x++)
    {
      if (map[y][x] == '.')
      {
        return;
      }
    }
  }

  int num_door_positions_considered = 0;
  int door_x, door_y;

  if (!first_cave)
  {
    // Look for intersecting walls.
    // XXX: Scans whole cave but only
    //      needs to check along walls.
    for (int y = y0 ; y <= y1 ; y++)
    {
      for (int x = x0 ; x <= x1 ; x++)
      {
        int s = (x == x0 || x == x1);
        int t = (y == y0 || y == y1);

        // If we are not at a corner,
        // and we have an existing wall here...
        if (s ^ t && map[y][x] == '#')
        {
          // ...then the number of possible door placements
          // we've seen total is increased by one...
          num_door_positions_considered++;

          // ...and we have a 1 in d chance of using the current
          // x, y position as the placement for the door of this
          // cave. The iterations that follow have a decreasing
          // but still existing possibility of updating the
          // position where we eventually place the door.
          //
          // Further, note that rangedrand(0, 0) is always 0
          // as pointed out by Joker-VD on GitHub, so at this
          // point in the control flow it is guaranteed that
          // a door will be placed.
          if (rangedrand(0, num_door_positions_considered) == 0)
          {
            door_x = x;
            door_y = y;
          }
        }
      }
    }

    // If we have no door, because of no neighbouring
    // cave walls, then we do not create this cave.
    if (num_door_positions_considered == 0)
    {
      return;
    }
  }

  // Create corners ('!'), walls ('#') and floor ('.') for this cave.
  for (int y = y0 ; y <= y1 ; y++)
  {
    for (int x = x0 ; x <= x1 ; x++)
    {
      int s = (x == x0 || x == x1);
      int t = (y == y0 || y == y1);

      map[y][x] = s && t ? '!' : s ^ t ? '#' : '.';
    }
  }

  if (first_cave)
  {
    // Player starts in first cave. There is nothing else in this cave.
    //
    // XXX: Upper bound exclusive are y1 - 1 and x1 - 1 here, so player will never
    //      land on the rightmost column of the floor nor on the bottom-most row
    //      of the floor, which I think is probably unintended.
    map[rangedrand(y0 + 1, y1 - 1)][rangedrand(x0 + 1, x1 - 1)] = '@';
  }
  else
  {
    // Other caves have one door and contain between one and six entities.

    // Place door. 50/50 chance of the door being either "'" or '+'.
    //
    // http://angband.oook.cz/stuff/manual.txt,
    // as pointed out by HN user homarp, gives:
    //
    //   ' An open/broken door
    //   + A closed door
    //
    // (My initial guess was that ' meant unlocked and + meant locked.)
    map[door_y][door_x] = rand() % 2 ? '\'' : '+';

    // Generate and place entities.
    for (int j = 0 ; j < rangedrand(1, 7) ; j++)
    {
      int ent;

      // 25% chance of creating a '$' entity. Means gold or gems (my guess was treasure).
      if (rangedrand(0, 4) == 0)
      {
        ent = '$';
      }
      // 75% chance of an ASCII character between 'A' and '~'. These symbols
      // represent entities ranging from angelic beings to light sources,
      // tools, chests, junk, sticks, skeletons etc.
      else
      {
        ent = rangedrand(65, 127);
      }

      // XXX: Same as with the player wrt positioning.
      map[rangedrand(y0 + 1, y1 - 1)][rangedrand(x0 + 1, x1 - 1)] = ent;
    }
  }
}
