// ASCII random dungeon generator.
//
// Robert Nystrom
// @munificentbob
// for Ginny
// 2008-2019

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

void cave(int);

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

void cave(int s)
{
  int w = rangedrand(5, 15);
  int h = rangedrand(3, 9);
  int t = rangedrand(1, W - w - 1);
  int u = rangedrand(1, H - h - 1);

  for (int y = u - 1; y < u + h + 2; y++)
  {
    for (int x = t - 1; x < t + w + 2; x++)
    {
      if (map[y][x] == '.')
      {
        return;
      }
    }
  }

  int d = 0;
  int e, f;

  if (s == 0)
  {
    for (int y = u - 1; y < u + h + 2; y++)
    {
      for (int x = t - 1; x < t + w + 2; x++)
      {
        int s = x < t || x > (t + w);
        int t = y < u || y > (u + h);

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

  for (int y = u - 1; y < u + h + 2; y++)
  {
    for (int x = t - 1; x < t + w + 2; x++)
    {
      int s = x < t || x > t + w;
      int t = y < u || y > u + h;

      map[y][x] = s && t ? '!' : s ^ t ? '#' : '.';
    }
  }

  if (d > 0)
  {
    map[f][e] = rand() % 2 ? '\'' : '+';
  }

  for (int j = 0; j < (s ? 1 : rangedrand(1, 7)); j++)
  {
    map[rangedrand(0, h) + u][rangedrand(t, w + t)] = s ? '@' : rangedrand(0, 4) == 0 ? '$' : rangedrand(65, 127);
  }
}
