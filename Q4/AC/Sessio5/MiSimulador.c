#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

struct Cache {
  unsigned int tag;
  char utilitzat;
};

struct Cache C[128];


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */

	for (int i = 0; i < 128; ++i){
		C[i].utilitzat = 'n';
	}
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement = 0;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */

	
	bloque_m = address / 32;  
	linea_mc = bloque_m % 128;
	byte = address % 32;
	tag = address / 4096;
	if (C[linea_mc].utilitzat == 's' && C[linea_mc].tag == tag) {
		miss = 0;	
	} else {
		miss = 1;
		if (C[linea_mc].utilitzat != 'n') {
			tag_out = C[linea_mc].tag;
			replacement = 1;
		} else {
			C[linea_mc].utilitzat = 's';
		}
		C[linea_mc].tag = tag;
	}
	











	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  
  
}
