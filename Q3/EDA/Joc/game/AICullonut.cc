#include "Player.hh"
 #include <limits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Collonut


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
    typedef vector<VI> MI;
    typedef vector<VB> MB;
    typedef vector<VP> MP;
    const int MAX_ITERATIONS = 15;


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
            if (cell(p).type != Rock and (cell(p).id == -1 or unit(cell(p).id).player != me())) {
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

  //Retorna el cami mes llarg que passi per mes posicions que no son celes seves
  VP bfs_pioneers(Pos& pioneer) {
    

  }

  void move_pioneers() {
    VI P = pioneers(me());
    for (int id : P) {
      Pos player = unit(id).pos;
      VP bfs = bfs_pioneers(player);
      for (auto p : bfs) cerr << p << " ____ ";
      cerr << endl;
      if (not bfs.empty()) direccio_furyan(player, bfs[0], id);
      else {
        Dir d;
        do {
          d = Dir(random(0, DirSize - 3));
        } while (cell(player + d).type != Cave);
        command(id, d);
      }
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