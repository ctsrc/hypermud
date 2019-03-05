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
  srand((int) time(NULL));

  // Initialize map to consist purely of blank spaces.
  for (int y = 0; y < H; y++)
  {
    for (int x = 0; x < W; x++)
    {
      map[y][x] = ' ';
    }
  }

  // Generate dungeon.
  for (int j = 0; j < 1000; j++)
  {
    cave(j == 0);
  }

  // Print generated dungeon.
  for (int y = 0; y < H; y++)
  {
    for (int x = 0; x < W; x++)
    {
      int c = map[y][x];

      putchar(c == '!' ? '#' : c);

      if (x == W - 1)
      {
        printf("\n");
      }
    }
  }

  return 0;
}

void cave (bool first_cave)
{
  // Dimensions of cave are w * h.
  int w = rangedrand(5, 15);
  int h = rangedrand(3, 9);

  // Upper left corner of cave floor is at coord (x, y) = (x0, y0).
  int x0 = rangedrand(1, W - w - 1);
  int y0 = rangedrand(1, H - h - 1);

  // If there is a floor present already within
  // the bounds where we were going to create
  // a new cave then do not create a new cave here.
  for (int y = y0 - 1; y < y0 + h + 2; y++)
  {
    for (int x = x0 - 1; x < x0 + w + 2; x++)
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
    for (int y = y0 - 1; y < y0 + h + 2; y++)
    {
      for (int x = x0 - 1; x < x0 + w + 2; x++)
      {
        int s = x < x0 || x > (x0 + w);
        int t = y < y0 || y > (y0 + h);

        // If we are not at a corner (I think),
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
          if (rangedrand(0, num_door_positions_considered) == 0)
          {
            door_x = x;
            door_y = y;
          }
        }
      }
    }

    // If we have no door, either because of no neighbouring caves
    // or because of very unlikely bad luck with regards to random
    // numbers then we do not create this cave.
    if (num_door_positions_considered == 0)
    {
      return;
    }
  }

  // Create floor ('.'), walls ('#') and corners ('!') for this cave.
  for (int y = y0 - 1; y < y0 + h + 2; y++)
  {
    for (int x = x0 - 1; x < x0 + w + 2; x++)
    {
      int s = x < x0 || x > x0 + w;
      int t = y < y0 || y > y0 + h;

      map[y][x] = s && t ? '!' : s ^ t ? '#' : '.';
    }
  }

  if (first_cave)
  {
    // Player starts in first cave. There is nothing else in this cave.
    //
    // XXX: Upper bound exclusive is w + x0 here, so player will never
    //      land on the rightmost column of the floor, which I think is
    //      probably unintended.
    map[rangedrand(0, h) + y0][rangedrand(x0, w + x0)] = '@';
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
    for (int j = 0; j < rangedrand(1, 7); j++)
    {
      int ent;

      // 25% chance of creating a '$' entity. Presumably means treasure.
      if (rangedrand(0, 4) == 0)
      {
        ent = '$';
      }
      // 75% chance of an ASCII character between 'A' and '~'. I imagine monsters etc.
      else
      {
        ent = rangedrand(65, 127);
      }

      map[rangedrand(0, h) + y0][rangedrand(x0, w + x0)] = ent;
    }
  }
}
