#include "Player.hh"
 #include <limits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Epc_v2


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
    typedef vector<int> VI;
    typedef vector<bool> VB;
    typedef vector<Pos> VP;
    typedef vector<pair<int,int>> VPii;
    typedef vector<VI> MI;
    typedef vector<VB> MB;
    typedef vector<VP> MP;
    const int MAX_ITERATIONS = 15;

  bool hi_ha_hellhound(Pos& p) {
    VI H = hellhounds();
    int radi = 3;
    for (int id : H) {
      Pos pos_h = unit(id).pos;
      int x_i, x_f, y_i, y_f;
      x_i = x_f = pos_h.i;
      y_i = y_f = pos_h.j;
      if (x_i < 2) {
        x_i = 0;
        x_f += 2;
      } else if (x_f > 37) {
        x_i += 2;
        x_f = 39;
      } else {
        x_i -= 2;
        x_f += 2;
      }
        y_i -= 2;
        y_f += 2;
      y_i = (y_i+cols())%cols();
      y_f %= cols();
      for (int i = x_i; i <= x_f; ++i) {
        for (int j = y_i; j <= y_f; ++j) {
          if (i == p.i and j == p.j) return true;
        }
      }  

    }
    return false;
  }
  bool hi_ha_hellhound_f(Pos& p) {
    VI H = hellhounds();
    for (int id : H) {
      Pos pos_h = unit(id).pos;
      int x_i, x_f, y_i, y_f;
      x_i = x_f = pos_h.i;
      y_i = y_f = pos_h.j;
      if (x_i < 1) {
        x_i = 0;
        x_f += 1;
      } else if (x_f > 38) {
        x_i += 1;
        x_f = 39;
      } else {
        x_i -= 1;
        x_f += 1;
      }
        y_i -= 1;
        y_f += 1;
      y_i = (y_i+cols())%cols();
      y_f %= cols();
      for (int i = x_i; i <= x_f; ++i) {
        for (int j = y_i; j <= y_f; ++j) {
          if (i == p.i and j == p.j) return true;
        }
      }  

    }
    return false;
  }

  pair<bool, VP> furyans_bfs(Pos furyan) {
    MB Visitats(rows(), VB(cols(), false));
    MP Parents(rows(), VP(cols(), Pos(-1, -1, -1)));  // Store parent positions for each visited position
    Visitats[furyan.i][furyan.j] = true;
    int iterations = MAX_ITERATIONS;
    queue<Pos> Q;
    Q.push(furyan);
    while (iterations > 0 and not Q.empty()) {
      Pos Top = Q.front();
      Q.pop();
      for (Dir d = Bottom; d <= LB; d = static_cast<Dir>(d + 1)) {
        Pos p = Top + d;
        p = Pos(p.i, (p.j + cols()) % cols(), p.k);
        if (pos_ok(p)) {
          if (not Visitats[p.i][p.j]) {
            Visitats[p.i][p.j] = true;
            Parents[p.i][p.j] = Top;  // Store the parent position
            if (not hi_ha_hellhound_f(p) and cell(p).type != Rock and (cell(p).id == -1 or unit(cell(p).id).player != me())) {
              Q.push(p);
              if (cell(p).id != -1 and unit(cell(p).id).player != me() and unit(cell(p).id).type == Pioneer) {
                // Fent el cami
                VP cami;
                while (p != furyan) {
                  cami.push_back(p);
                  p = Parents[p.i][p.j];
                }
                reverse(cami.begin(), cami.end());
                return {true, cami};
              }
            }
          }
        }
      }
      --iterations;
    }
  return {false, VP()};  // No hi ha cami
  }

  void direccio_furyan(Pos& player, Pos& enemy, int id) {
    for (Dir d = Bottom; d <= LB; d = static_cast<Dir>(d+1)) {
      if (player+d == enemy) command(id, d);
    }
  }

  void move_furyans(){
    VI F = furyans(me());
    for (int id : F) {
      Pos player = unit(id).pos;
      pair<bool, VP> bfs2 = furyans_bfs(player);
      //Es mou cap a un enemic si el tÃ© aprop, sino es mou random
      if (bfs2.first)  direccio_furyan (player, bfs2.second[0], id);
      else {
        Dir d;
        do {
          d = Dir(random(0, DirSize - 3));
        } while (cell(player + d).type == Rock);
        command(id, d);
      }
    }
  }
  
  bool cami_mes_llarg(MI& dist, MI& nodes, Pos& p, Pos& max) {
    return nodes[p.i][p.j] > nodes[max.i][max.j] && dist[p.i][p.j] - dist[max.i][max.j] > 0;
} 
  
  bool hi_ha_furyan(Pos& p) {
    VPii pos = {{0,1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (auto d : pos) {
      Pos aux = Pos(p.i+d.first, p.j+d.second, p.k);
      if (aux.i < 0) aux.i = 0;
      else if (aux.i > 39) aux.i = 39;
      aux.j = (aux.j+cols())%cols();
      if (cell(aux).type == Cave and cell(aux).id != -1 and unit(cell(aux).id).type == Furyan and unit(cell(aux).id).player != me()) return true;
    }
  return false;
  }

  //Retorna el cami mes llarg que passi per mes posicions que no son celes seves
  VP dijkstra_pioneers(Pos& pioneer) {
    Pos max = pioneer;
    MI dist (rows(), VI(cols(), -2));
    MP Parents(rows(), VP(cols(), Pos(-1, -1, -1)));
    MI gemes (rows(), VI(cols(), 0));
    MB visitats(rows(), VB(cols(), false));

    dist[pioneer.i][pioneer.j] = 0;
    gemes[pioneer.i][pioneer.j] = 0;

    priority_queue<pair<int, Pos>, vector<pair<int, Pos>>, greater<pair<int, Pos>>> Cua;
    Cua.push({0, pioneer});
    
    int iterations = 20;
    while(iterations > 0 and not Cua.empty()) {
      Pos Top = Cua.top().second;
      Cua.pop();
      if (not visitats[Top.i][Top.j]) { 
        visitats[Top.i][Top.j] = false;
        for (Dir d = Bottom; d <= LB; d = static_cast<Dir>(d + 1)) {
          Pos p = Top + d;
          p = Pos(p.i, (p.j + cols()) % cols(), p.k);
          if (pos_ok(p)) {
            if (cell(p).type == Rock) { //Si es una roca la volem marcar com a visitada pero no podem passar per alla
              dist[p.i][p.j] = -1;
            }
            else { //Mirar si la cela es seva o no
              if (cell(p).type == Cave) {
                int c, b;
                if (cell(p).owner != me())
                  c = b = 1;
                else { //Sino es que es meva
                  b = 0;
                  c = 2;
                }
              if (cell(p).id == -1 and (dist[p.i][p.j] == -2 or dist[Top.i][Top.j] + c < dist[p.i][p.j] or (dist[Top.i][Top.j] + c == dist[p.i][p.j] and  gemes[p.i][p.j] < gemes[Top.i][Top.j]+b))){
                if (not hi_ha_hellhound(p) and not hi_ha_furyan(p)) {
                  dist[p.i][p.j] = dist[Top.i][Top.j] + c;
                  gemes[p.i][p.j] = gemes[Top.i][Top.j] + b;
                  Parents[p.i][p.j] = Top;
                  if (gemes[p.i][p.j] > gemes[max.i][max.j]) 
                    max = p;
                  Cua.push({dist[p.i][p.j], p});
                }
              }

              }
            }
          }
        }
      }
      --iterations;
    }
    VP cami;
    while (max != pioneer) {
      cami.push_back(max);
      max = Parents[max.i][max.j];
    }
    reverse(cami.begin(), cami.end());
    return cami;
  }

  void move_pioneers() {
  VI P = pioneers(me());
  for (int id : P) {
    Pos player = unit(id).pos;
    VP bfs = dijkstra_pioneers(player);
    if (not bfs.empty()) direccio_furyan(player, bfs[0], id);
  }
  } 

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_furyans();
    move_pioneers();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);