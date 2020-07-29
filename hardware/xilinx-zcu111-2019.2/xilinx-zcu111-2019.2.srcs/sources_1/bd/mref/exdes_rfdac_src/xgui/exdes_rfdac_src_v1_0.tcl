# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "default_signal_type" -parent ${Page_0}
  ipgui::add_param $IPINST -name "enable_override" -parent ${Page_0}
  ipgui::add_param $IPINST -name "initial_interword_offset" -parent ${Page_0}


}

proc update_PARAM_VALUE.default_signal_type { PARAM_VALUE.default_signal_type } {
	# Procedure called to update default_signal_type when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.default_signal_type { PARAM_VALUE.default_signal_type } {
	# Procedure called to validate default_signal_type
	return true
}

proc update_PARAM_VALUE.enable_override { PARAM_VALUE.enable_override } {
	# Procedure called to update enable_override when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.enable_override { PARAM_VALUE.enable_override } {
	# Procedure called to validate enable_override
	return true
}

proc update_PARAM_VALUE.initial_interword_offset { PARAM_VALUE.initial_interword_offset } {
	# Procedure called to update initial_interword_offset when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.initial_interword_offset { PARAM_VALUE.initial_interword_offset } {
	# Procedure called to validate initial_interword_offset
	return true
}


proc update_MODELPARAM_VALUE.enable_override { MODELPARAM_VALUE.enable_override PARAM_VALUE.enable_override } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.enable_override}] ${MODELPARAM_VALUE.enable_override}
}

proc update_MODELPARAM_VALUE.default_signal_type { MODELPARAM_VALUE.default_signal_type PARAM_VALUE.default_signal_type } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.default_signal_type}] ${MODELPARAM_VALUE.default_signal_type}
}

proc update_MODELPARAM_VALUE.initial_interword_offset { MODELPARAM_VALUE.initial_interword_offset PARAM_VALUE.initial_interword_offset } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.initial_interword_offset}] ${MODELPARAM_VALUE.initial_interword_offset}
}

