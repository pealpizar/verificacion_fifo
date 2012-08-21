/**Aquí van a vivir todos los elementos de verificación
 * voy a redactar un par de elementos para sin más que las conecciones
 */
#include "verif_elements.h"
#include "scoreboard.hpp"
#include "verification_defs.hpp"

void generador::cnt_clk_gen (){
  if (clk.read()){
    cnt_periodo++;
  }
}

void generador::prc_generador () {
  
  if (reset.read()) {  
    if (cnt_periodo >= 2) {
      tmp_reset = true;
      cnt_periodo = 0;
    }
  } else {
    if (tmp_reset) {
      cnt_periodo = 0;
      tmp_reset = false;
      //inicialización de la velocidad
      switch (vel_act) {
        case -1:
          vel_act = (tipo == 1)? 0:VEL_NUM-1;
          break;
        case 0:
          vel_act = (tipo == 1)? 1: 0;
          break;
        case 1:
          vel_act = (tipo == 1)? 2: 0;
          break;
        case 2:
          vel_act = (tipo == 1)? 2: 1;
          break;
      }
    }
    if (cnt_periodo < (velocidades[vel_act]/2) ){
      if (tipo) {
        data_rnd = rand() % 256;
        data.write(data_rnd);
      }
    } else if (cnt_periodo == velocidades[vel_act]) {
      if (vel_act != 1) {
        read_write.write(true);
      } else if ((rand() %2) == 0) {
        read_write.write(true);
      }
    } else if ( cnt_periodo == (velocidades[vel_act]+2) ) {
      read_write. write(false);
      cnt_periodo = 0;
    }
  }
}

void sen_checker::cnt_clk_sen (){
  static bool tmp_clk = false;
  if (tmp_clk && !clk.read()){
    cnt_periodo++;
  } else {
    tmp_clk = clk.read();
  }
}

void sen_checker::prc_sen_checker () {
  if (reset.read()) {  
    if (cnt_periodo >= 2) {
      cnt_periodo = 0;
      cnt_data = 0;
      pasos = 0;
      if ( !full.read() && !half_full.read() && !data_present.read()) {
        report.coverage = RESET_CORRECT;
        report.status = PASS;
        scoreboard.log(report);
      } else {
        report.coverage = RESET_CORRECT;
        report.status = FAIL;
        scoreboard.log(report);
      }
    }
  } else {
    if (!data_present.read()) {
      if (!full.read() && !half_full.read()) {
        report.coverage = DATA_PRESENT_CORRECT;
        report.status = PASS;
        scoreboard.log(report);
      } else {
        report.coverage = DATA_PRESENT_CORRECT;
        report.status = FAIL;
        scoreboard.log(report);
      }
    } else {
      //Revisa que las señales se encuntren levantadas solo cuando es debido
      if (full.read() && (cnt_data == DATA_LENGTH)) {
        report.coverage = FULL_SIGNAL;
        report.status = PASS;
        scoreboard.log(report);
      } else {
        report.coverage = FULL_SIGNAL;
        report.status = FAIL;
        scoreboard.log(report);
      }
      if (half_full.read() && (cnt_data == DATA_LENGTH/2)) {
        report.coverage = HALF_FULL_SIGNAL;
        report.status = PASS;
        scoreboard.log(report);
      } else {
        report.coverage = HALF_FULL_SIGNAL;
        report.status = FAIL;
        scoreboard.log(report);
      }
      
      switch (pasos) {
        case 0:
          cnt_periodo = 0;
          if (write.read()) {
            pasos = 1;
          } else if (read.read()) {
            pasos = 2;
          }
          break;
        case 1:
          if (write.read() && cnt_periodo == 1) {
            if (cnt_data == 0) {
              cnt_data++;
              if (data_present.read()) {
                report.coverage = DATA_PRESENT_CORRECT;
                report.status = PASS;
                scoreboard.log(report);
              } else {
                report.coverage = DATA_PRESENT_CORRECT;
                report.status = FAIL;
                scoreboard.log(report);
              }
            } else {
              cnt_data = (cnt_data == DATA_LENGTH)? cnt_data: ++cnt_data;
              if (cnt_data == (DATA_LENGTH/2)) {
                if (half_full.read()) {
                  report.coverage = HALF_FULL_SIGNAL;
                  report.status = PASS;
                  scoreboard.log(report);
                } else {
                  report.coverage = HALF_FULL_SIGNAL;
                  report.status = FAIL;
                  scoreboard.log(report);
                }
                break;
              }
              if (cnt_data == DATA_LENGTH) {
                if (full.read()) {
                  report.coverage = FULL_SIGNAL;
                  report.status = PASS;
                  scoreboard.log(report);
                } else {
                  report.coverage = FULL_SIGNAL;
                  report.status = FAIL;
                  scoreboard.log(report);
                }
                break;
              }
            }
            pasos = 0;
          }
          break;
        case 2:
          if (read.read() && cnt_periodo == 1) {
            if (cnt_data == 0) {
              if (data_present.read()) {
                report.coverage = DATA_PRESENT_CORRECT;
                report.status = PASS;
                scoreboard.log(report);
              } else {
                report.coverage = DATA_PRESENT_CORRECT;
                report.status = FAIL;
                scoreboard.log(report);
              }
            } else {
              cnt_data = (cnt_data == 0)? cnt_data: --cnt_data;
              if (cnt_data == (DATA_LENGTH/2)) {
                if (half_full.read()) {
                  report.coverage = HALF_FULL_SIGNAL;
                  report.status = PASS;
                  scoreboard.log(report);
                } else {
                  report.coverage = HALF_FULL_SIGNAL;
                  report.status = FAIL;
                  scoreboard.log(report);
                }
                break;
              }
              if (cnt_data == DATA_LENGTH) {
                if (half_full.read()) {
                   report.coverage = FULL_SIGNAL;
                  report.status = PASS;
                  scoreboard.log(report);
                } else {
                  report.coverage = FULL_SIGNAL;
                  report.status = FAIL;
                  scoreboard.log(report);
                }
                break;
              }
            }
            pasos = 0;
          }
          break;
      }
    }
  }
}

void datos_checker::prc_datos_checker () {
  //Aquí debe ir la carnita
}

