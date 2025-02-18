#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
 struct Cache{
 unsigned int tag;
 int bValidesa;
 };
 
 struct Cache C[128];
 int acierto = 0;
 int fallo = 0;




/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; ++i){
        C[i].bValidesa = 0;
 	acierto = 0;
 	fallo = 0;
    }


}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */
	byte = address % 32;
	bloque_m = address / 32;
	linea_mc = bloque_m % 128;
	tag = address / 4096;
	miss = (C[linea_mc].tag != tag || C[linea_mc].bValidesa == 0);
	fallo += miss;
	acierto += !miss;
	if (LE == lectura) {
		if(miss) lec_mp = 1;
		else lec_mp = 0;
		esc_mp = mida_esc_mp = 0;
		if (miss) mida_lec_mp = 32;
		else mida_lec_mp = 0;
	} else {
		lec_mp = mida_lec_mp = 0;
		esc_mp = mida_esc_mp = 1;
	}
	replacement = ((C[linea_mc].bValidesa == 1 && C[linea_mc].tag != tag )&& lec_mp);
	if (lec_mp) {
		if (replacement) tag_out = C[linea_mc].tag;
		else if (lec_mp) C[linea_mc].bValidesa = 1;
		C[linea_mc].tag = tag;
	} 


	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  printf("Fallos: %d, Aciertos: %d \n", fallo, acierto);
  
}
