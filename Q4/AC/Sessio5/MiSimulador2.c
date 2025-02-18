#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

struct Cache {
  unsigned int tag1;
  unsigned int tag2;
  char utilitzat1;
  char utilitzat2;
  int lru;
};

struct Cache C[64];




/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 64; ++i){
		C[i].utilitzat1 = C[i].utilitzat2 = 'n';
	}


}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss=0;	   // boolea que ens indica si es miss
	unsigned int replacement=0;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
	
	byte = address % 32;
	bloque_m = address / 32;
	conj_mc = bloque_m % 64;
	tag = address / 2048;
	
	if (C[conj_mc].utilitzat1 == 's' && C[conj_mc].tag1 == tag) {
		miss = 0;
		C[conj_mc].lru = 1;
		via_mc = 0;
	}
	else if (C[conj_mc].utilitzat2 == 's' && C[conj_mc].tag2 == tag){
		miss = 0;
		C[conj_mc].lru = 0;
		via_mc = 1;	
	} else{
		miss = 1;
		if (C[conj_mc].utilitzat1 == 'n') {
			C[conj_mc].tag1 = tag;
			C[conj_mc].lru = 1;
			C[conj_mc].utilitzat1 = 's';
			via_mc = 0;
				
		} else if (C[conj_mc].utilitzat2 == 'n') {
			C[conj_mc].tag2 = tag;
			C[conj_mc].lru = 0;
			C[conj_mc].utilitzat2 = 's';
			via_mc = 1;
		}else{
			if (C[conj_mc].lru == 0) {
				tag_out = C[conj_mc].tag1;
				C[conj_mc].tag1 = tag;
				C[conj_mc].lru = 1;
				via_mc = 0;
			}
			else {
				tag_out = C[conj_mc].tag2;
				C[conj_mc].tag2 = tag;
				C[conj_mc].lru = 0;
				via_mc = 1;
			}
			replacement = 1;;
		}
	}


	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  
  
}
