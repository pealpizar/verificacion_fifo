/**Este es el archivo de jerarquía más alto. En el sólo deben encontrarse 
 * instanciados los elementos y tal vez el clock. Por ahora sólo llamando al 
 * DUT.
 */
#include "srl_fifo_16.h"
#include "verif_elements.h"
#include "fifo_data_monitor.h"
#include "scoreboard.hpp"

// global variable for scoreboarding
scoreboard_c scoreboard;

int sc_main(int argc, char* argv[]) {
  sc_signal< sc_lv<8> >  data_in, data_out;
  sc_signal< bool > reset, write, read, full, half_full, data_present, clk, tipo_w, tipo_r;
  int seed;
  seed = rand();

  tipo_w.write(1);
  tipo_r.write(0);

  //Declaración de los bloques
  //DUT
  fifo_srl dut("srl_fifo_16");
  dut.data_in(data_in);
  dut.data_out(data_out);
  dut.reset(reset);
  dut.write(write);
  dut.read(read);
  dut.full(full);
  dut.half_full(half_full);
  dut.data_present(data_present);
  dut.clk(clk);

  //Generador de escrituras
  generador write_gen("gen_escrituras");
  write_gen.data(data_in);
  write_gen.reset(reset);
  write_gen.read_write(write);
  write_gen.tipo(tipo_w);
  write_gen.clk(clk);
  write_gen.seed = seed;

  //Generador de lecturas
  generador read_gen("gen_lecturas");
  read_gen.data(data_out);
  read_gen.reset(reset);
  read_gen.read_write(read);
  read_gen.tipo(tipo_r);
  read_gen.clk(clk);
  read_gen.seed = seed;

  sen_checker cheq_sen("cheq_signals");
  cheq_sen.data_in(data_in);
  cheq_sen.data_out(data_out);
  cheq_sen.reset(reset);
  cheq_sen.write(write);
  cheq_sen.read(read);
  cheq_sen.full(full);
  cheq_sen.half_full(half_full);
  cheq_sen.data_present(data_present);
  cheq_sen.clk(clk);

  fifo_mon cheq_fifo("modelo_fifo");
  cheq_fifo.data_in(data_in);
  cheq_fifo.data_out(data_out);
  cheq_fifo.reset(reset);
  cheq_fifo.write(write);
  cheq_fifo.read(read);
  cheq_fifo.clk(clk);
  sc_start();
  sc_stop();

  //scoreboard logging

  
  return(0);
}

