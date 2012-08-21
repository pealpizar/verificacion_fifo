#ifndef __SRL_FIFO_32__
#define __SRL_FIFO_32__
/**En este archivo se encuentra la declaración de la clase interfaz.
 * Esta clase tendrá acceso a todas las señales y podrá ser llamada. 
 * Utilizando este elemento es como si el DUT fuera systemC.
 * */
//FIXME: Agregar aquí los comandos de precompilador para solo agregar un 
//systemC
#include <systemc.h>

class srl_fifo_32 : public ncsc_foreign_module
{
  public:
    sc_in< sc_lv<8> >  data_in;
    sc_out< sc_lv<8> > data_out;
    sc_in< bool >      reset;
    sc_in< bool >      write;
    sc_in< bool >      read;
    sc_out< bool >     full;
    sc_out< bool >     half_full;
    sc_out< bool >     data_present;
    sc_in_clk          clk;
    
    srl_fifo_32(sc_module_name nm)
      : ncsc_foreign_module(nm), data_in("data_in"), 
      data_out("data_out"), reset("reset"), write ("write"), read("read"), 
      full("full"), half_full("half_full"), data_present("data_present"), 
      clk("clk"){}
    const char*hdl_name()const {return "srl_fifo_32";}
};

#endif // __SRL_FIFO_32__
