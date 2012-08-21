#ifndef __SRL_FIFO_16__
#define __SRL_FIFO_16__
/**En este archivo se encuentra la declaración de la clase interfaz.
 * Esta clase tendrá acceso a todas las señales y podrá ser llamada. 
 * Utilizando este elemento es como si el DUT fuera systemC.
 * */
//FIXME: Agregar aquí los comandos de precompilador para solo agregar un 
//systemC
#include <systemc.h>

class fifo_srl : public sc_module
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
    
    fifo_srl(sc_module_name nm)
      : sc_module (nm), data_in("data_in"), 
      data_out("data_out"), reset("reset"), write ("write"), read("read"), 
      full("full"), half_full("half_full"), data_present("data_present"), 
      clk("clk"){}
};
/*
library IEEE;
use IEEE.std_logic_1164.all;
entity vmod is
generic (
pi :integer :=0;
pd :real :=5.69;
ps1 :string :="abcd";
ps2 :string :="xyz");
port (
clk:std_logic;
input :in std_logic_vector(31 downto 0);
output :out std_logic_vector(31 downto 0)
);
end;
--Generated SystemC shell file
#include "systemc.h"
class vmod :public ncsc_foreign_module {
public:
sc_in <bool >clk;
sc_in <sc_lv <32>>input;
sc_out <sc_lv <32>>output;
vmod(
sc_module_name nm,
int pi,
double pd,
sc_string ps1,
sc_string ps2
):ncsc_foreign_module(nm)
,clk("clk")
,input("input")
,output("output")
{
ncsc_set_hdl_param("pi",pi);
ncsc_set_hdl_param("pd",pd);
ncsc_set_hdl_param("ps1",ps1);
ncsc_set_hdl_param("ps2",ps2);
}
const char*hdl_name()const {return "vmod";}
};
*/

#endif // __SRL_FIFO_16__
