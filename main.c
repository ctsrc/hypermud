/*
 * ASCII random dungeon generator.
 *
 * Robert Nystrom
 * @munificentbob
 * for Ginny
 * 2008-2019
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Number of characters wide and high.
const int W = 80;
const int H = 40;

int map[40][80];

/*
 * Return a random integer in range [lower_bound_incl, upper_bound_excl).
 */
int rangedrand(int lower_bound_incl, int upper_bound_excl)
{
  return lower_bound_incl + (rand() % (upper_bound_excl - lower_bound_incl));
}

void cave(bool);

int main(int argc, const char *argv[])
{
  // Set seed for pseudo-random generator
  srand((int) time(NULL));

  // Initialize map to consist purely of blank spaces
  for (int y = 0; y < H; y++)
  {
    for (int x = 0; x < W; x++)
    {
      map[y][x] = ' ';
    }
  }

  // Generate dungeon
  for (int j = 0; j < 1000; j++)
  {
    cave(j == 0);
  }

  // Print generated dungeon
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

void cave(bool first_cave)
{
  // Dimensions of cave are w * h
  int w = rangedrand(5, 15);
  int h = rangedrand(3, 9);

  // Upper left corner of cave is at coord (x, y) = (u, v)
  int u = rangedrand(1, W - w - 1);
  int v = rangedrand(1, H - h - 1);

  // If there is a floor present already within
  // the bounds where we were going to create
  // a new cave then do not create a new cave here
  for (int y = v - 1; y < v + h + 2; y++)
  {
    for (int x = u - 1; x < u + w + 2; x++)
    {
      if (map[y][x] == '.')
      {
        return;
      }
    }
  }

  int d = 0;
  int e, f;

  if (!first_cave)
  {
    for (int y = v - 1; y < v + h + 2; y++)
    {
      for (int x = u - 1; x < u + w + 2; x++)
      {
        int s = x < u || x > (u + w);
        int t = y < v || y > (v + h);

        if (s ^ t && map[y][x] == '#')
        {
          d++;

          if (rangedrand(0, d) == 0)
          {
            e = x;
            f = y;
          }
        }
      }
    }

    if (d == 0)
    {
      return;
    }
  }

  for (int y = v - 1; y < v + h + 2; y++)
  {
    for (int x = u - 1; x < u + w + 2; x++)
    {
      int s = x < u || x > u + w;
      int t = y < v || y > v + h;

      map[y][x] = s && t ? '!' : s ^ t ? '#' : '.';
    }
  }

  if (d > 0)
  {
    map[f][e] = rand() % 2 ? '\'' : '+';
  }

  // Player starts in first cave. There is nothing else in this cave.
  if (first_cave)
  {
    map[rangedrand(0, h) + v][rangedrand(u, w + u)] = '@';
  }
  else
  {
    // Other rooms contain between one and six entities.
    for (int j = 0; j < rangedrand(1, 7); j++)
    {
      int ent;

      // 25% chance of each entity being '$'. Presumably means treasure.
      if (rangedrand(0, 4) == 0)
      {
        ent = '$';
      }
      // 75% of an ASCII character between 65 and 126. I imagine monsters etc.
      else
      {
        ent = rangedrand(65, 127);
      }

      map[rangedrand(0, h) + v][rangedrand(u, w + u)] = ent;
    }
  }
}
