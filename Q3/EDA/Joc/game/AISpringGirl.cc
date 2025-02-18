#include "Player.hh"
#include <queue>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME SpringGirl


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

int dist_hellhound(Pos p) {
    queue< pair<Pos, int> > Q;
    vector<vector<bool>> visited(40,vector<bool>(80,false));

    Q.push(make_pair(p, 0));

    while (not Q.empty()) {
        Pos act = Q.front().first;
        int dist = Q.front().second;

        Q.pop();

        if (pos_ok(act) and not visited[act.i][act.j]) {
            visited[act.i][act.j] = true;

            for (int i = 0; i < 8; ++i) {
                Pos seg = act + Dir(i);
                int id_seg = cell(seg).id;

                if (pos_ok(seg) and id_seg != -1 and unit(id_seg).type == Hellhound) 
                    return dist + 1;

                if (pos_ok(seg) and cell(seg).type != Rock and cell(seg).type != Elevator) Q.push(make_pair(seg, dist+1));
               
            }
        }   
    }

    return 0;
}

Dir huir(Pos ini) {
    int dist_max = 0;
    Dir d = None;

    if (pos_ok(ini)) {
        for (int i = 0; i < 8; ++i) {
            Pos seg = ini + Dir(i);

            if (pos_ok(seg) and cell(seg).id == -1 and cell(seg).type != Rock and cell(seg).type != Elevator) {
                int dist_act = dist_hellhound(seg);
               
                if (dist_act > dist_max) {
                    dist_max = dist_act;
                    d = Dir(i);
                }
            }
        }
    }
    return d;
}


Pos bfs_enemigo(int id) {
    queue<Pos> Q;    
    vector<vector<bool>> visited(40,vector<bool>(80,false));
    vector<vector<Pos>> directions(40,vector<Pos>(80));

    Pos p = unit(id).pos;
    Q.push(p);

    while (not Q.empty()) {
        Pos act = Q.front();
        Q.pop();

        //if (pos_ok(act) and not visited[act.i][act.j]) {
            Dir d = None;
            //visited[act.i][act.j] = true;

        for (int i = 0; i < 8; ++i) {
            Pos seg = act + Dir(i);
            //int id_seg = cell(seg).id;
            if (pos_ok(seg) and not visited[seg.i][seg.j]) {
                int id_seg = cell(seg).id;
                visited[seg.i][seg.j] = true;
                directions[seg.i][seg.j] = act;

                if (cell(seg).id != -1 and unit(id_seg).player != me() and 
                (unit(id_seg).type == Pioneer)) {
                    //Pos p = seg;
                    int id_p = cell(seg).id;
                    
                    while (directions[seg.i][seg.j] != p) 
                        seg = directions[seg.i][seg.j];
                    

                    return seg;
                }

                //if (cell(seg).id == -1 and cell(seg).type != Rock and cell(seg).type != Elevator) 
                if (cell(seg).type != Rock and cell(seg).id == -1)Q.push(seg);

                }
        }
        //} 
    }

    return {};
}

Pos bfs_conquista(int id) {
    queue<Pos> Q;    
    vector<vector<bool>> visited(40,vector<bool>(80,false));
    vector<vector<Pos>> directions(40, vector<Pos>(80));

    Pos p = unit(id).pos;
    Q.push(p);

    while (not Q.empty()) {
        Pos act = Q.front();
        Q.pop();

        //if (pos_ok(act) and not visited[act.i][act.j]) {
            //visited[act.i][act.j] = true;

            for (int i = 0; i < 8; ++i) {
                Pos seg = act + Dir(i);
                if (pos_ok(seg) and not visited[seg.i][seg.j] and cell(seg).id == -1 and cell(seg).type == Cave) {
                    visited[seg.i][seg.j] = true;
                    int id_seg = cell(seg).id;
                    directions[seg.i][seg.j] = act;
                    //cerr << directions[seg.i][seg.j] << "___" << act << endl;

                    if (cell(seg).owner != me()) {
                        while (directions[seg.i][seg.j] != p) 
                            seg = directions[seg.i][seg.j];

                        //cerr << seg << ":::" << p << endl;
                        return seg;
                    }                                       

                    Q.push(seg);
                }
            }
        //} 
    }

    return {};
}

Dir mueve_pers(Pos orig, Pos dest) {
    int id = cell(orig).id;
    
    for (int d = 0; d < 8; ++d) {
        Dir direc = Dir(d);

        if (orig+direc == dest) 
            return direc;
        
    }

    return None;
}

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    VI F = furyans(me());
    int n = F.size();

    for (int i = 0; i < n; ++i) {
        int id = F[i];
        Pos p = unit(id).pos;
        int dist = dist_hellhound(p);

        if (dist <= 4 and dist > 0) 
            command(id, huir(p));
        
        else {
            Pos desti = bfs_enemigo(id);
            Dir d = mueve_pers(p, desti);

            command(id, d);
        }
    }
    
    VI P = pioneers(me());
    int n2 = P.size();
    
    for (int i = 0; i < n2; ++i) {
        int id2 = P[i];
        Pos p2 = unit(id2).pos;
        int dist = dist_hellhound(p2);
     
        if (dist <= 4 and dist > 0) command(id2, huir(p2));
        else {
            Pos desti2 = bfs_conquista(id2);
            Dir d2 = mueve_pers(p2, desti2);

            command(id2, d2);
        }
    }
    
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);