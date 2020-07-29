# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "p_connection_width" -parent ${Page_0}
  ipgui::add_param $IPINST -name "p_connections" -parent ${Page_0}


}

proc update_PARAM_VALUE.p_connection_width { PARAM_VALUE.p_connection_width } {
	# Procedure called to update p_connection_width when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.p_connection_width { PARAM_VALUE.p_connection_width } {
	# Procedure called to validate p_connection_width
	return true
}

proc update_PARAM_VALUE.p_connections { PARAM_VALUE.p_connections } {
	# Procedure called to update p_connections when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.p_connections { PARAM_VALUE.p_connections } {
	# Procedure called to validate p_connections
	return true
}


proc update_MODELPARAM_VALUE.p_connections { MODELPARAM_VALUE.p_connections PARAM_VALUE.p_connections } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.p_connections}] ${MODELPARAM_VALUE.p_connections}
}

proc update_MODELPARAM_VALUE.p_connection_width { MODELPARAM_VALUE.p_connection_width PARAM_VALUE.p_connection_width } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.p_connection_width}] ${MODELPARAM_VALUE.p_connection_width}
}

