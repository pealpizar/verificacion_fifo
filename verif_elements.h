#ifndef __VERIF_ELEMENTS_H__
#define __VERIF_ELEMENTS_H__

/**Definiciones para las definiciones de los elementos de verificación
 */

#include <systemc.h>
#include "scoreboard.hpp"
#include "verification_defs.hpp"

#ifndef VEL_NUM
#define VEL_NUM 3
#endif /* VEL_NUM */

/**Este generador se puede dividir en dos o trabajar con el modelo in/out propuesto
 * */
SC_MODULE (generador) {
  sc_out< bool > read_write;
  sc_in_clk        clk;
  sc_inout< sc_lv<8> > data;
  sc_in < bool >   tipo,reset;
  //La velocidad esta expresada en ciclos de reloj
  int velocidades[VEL_NUM];
  //contador de ciclos de reloj
  int cnt_periodo;
  int seed;
  sc_uint<8> data_rnd;
  bool tmp_reset;
  int vel_act;
  void prc_generador ();
  void cnt_clk_gen ();
  log_t coverage;
  SC_CTOR(generador){
    velocidades[0] = 20;
    velocidades[1] = 30;
    velocidades[2] = 40;
    cnt_periodo = 0;
    tmp_reset = false;
    data_rnd = 0;
    vel_act = -1;
    SC_METHOD (prc_generador);
    sensitive << clk << reset;
    
    SC_METHOD (cnt_clk_gen);
    sensitive << clk;
  }
};

SC_MODULE (sen_checker){
  sc_in < sc_lv<8> > data_in, data_out;
  //half_ful no es indispensable implementarlo
  sc_in < bool > reset, write, read, full, data_present, half_full;
  sc_in_clk      clk;
  void cnt_clk_sen ();
  void prc_sen_checker();
  int cnt_periodo;
  int cnt_data;
  int pasos;
  log_t report;
  SC_CTOR (sen_checker) {
    cnt_periodo = 0;
    cnt_data = 0;
    pasos = 0;
    SC_METHOD (cnt_clk_sen);
      sensitive << clk;
    SC_METHOD (prc_sen_checker);
      sensitive << reset << write << read << full << data_present << half_full << clk;
  }
};

SC_MODULE (datos_checker){
  sc_in < sc_lv<8> > data_in, data_out;
  //Aquí las señales de estado no deberían ser necesarias
  sc_in < bool > reset, write, read;
  sc_in_clk      clk;
  void prc_datos_checker();
  SC_CTOR (datos_checker) {
    SC_METHOD (prc_datos_checker);
      sensitive << reset << write << read << clk;
  }
};

#endif /* __VERIF_ELEMENTS_H__ */
