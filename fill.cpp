#include <fstream>
using namespace std;
int continente(bool**, int, int);
int main()
{
  ifstream f("fill.in");
  int n, m;
  f >> n >> m;
  bool** a = new bool*[n];
  for (int i = 0; i < n; i++)
  {
    a[i] = new bool[m];
    for (int j = 0; j < m; j++)
      f >> a[i][j];
  }
  f.close();
  ofstream g("fill.out");
  g << continente(a, n, m);
  g.close();
  return 0;
}
void fill(int** a, int n, int m, int x, int y, int val)
{
  int dx[] = {-1, 0, 1, 0};
  int dy[] = {0, 1, 0, -1};
  struct Punct { int x, y; } stv[n*m];
  int vf = 0;
  stv[vf] = {x, y};
  while (vf >= 0)
  {
    Punct p = stv[vf--];
    a[p.x][p.y] = val*(-1);
    for (int d = 0; d < 4; d++)
    {
      Punct v;
      v.x = p.x + dx[d];
      v.y = p.y + dy[d];
      if (a[v.x][v.y] == 1)
        stv[++vf] = v;
    }
  }
}
int continente(bool** a, int n, int m)
{
  int** b = new int*[n+2];
  for (int i = 0; i < n+2; i++)
  {
    b[i] = new int[m+2];
    b[i][0] = b[i][m+1] = -1;
  }
  for (int j = 0; j < m+2; j++)
    b[0][j] = b[n+1][j] = -1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      b[i][j] = a[i-1][j-1];
  int nr = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (b[i][j] == 1)
      {
        nr++;
        fill(b, n+2, m+2, i, j, nr);
      }
  return nr;
}
