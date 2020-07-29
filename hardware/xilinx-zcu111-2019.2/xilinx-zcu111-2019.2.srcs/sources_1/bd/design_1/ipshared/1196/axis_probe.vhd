library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity axis_probe is
  port (
    clk : in std_logic; -- Keep packaging/IPI happy
    
    mon_tvalid : in std_logic;
    mon_tready : in std_logic;
    mon_tlast  : in std_logic;
    
    valid_op : out std_logic;
    ready_op : out std_logic;
    last_op  : out std_logic
    );
end axis_probe;

architecture synth of axis_probe is

-- ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
-- ATTRIBUTE X_INTERFACE_PARAMETER of mon: SIGNAL is "MODE Monitor";

begin
  valid_op  <= mon_tvalid;
  ready_op  <= mon_tready;
  last_op   <= mon_tlast;
end synth;
