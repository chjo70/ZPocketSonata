

/* this file is automatically generated */


Layer Layer::IPNET_TFTP {
}




/*********************************
 Component INCLUDE_IPTFTP_COMMON 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Component	INCLUDE_IPTFTP_COMMON {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Component INCLUDE_IPTFTPC 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Component	INCLUDE_IPTFTPC {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Component INCLUDE_IPTFTPS 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Component	INCLUDE_IPTFTPS {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Folder FOLDER_TFTP 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Folder	FOLDER_TFTP {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Layer Layer::IPNET_TFTP 
 original object sources located at 
 $(VSB_DIR) 
**********************************/
Layer	Layer::IPNET_TFTP {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(VSB_DIR)}
}


/*********************************
 Parameter TFTPS_DIRS 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTPS_DIRS {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Parameter TFTPS_RETRANSMIT_TIMEOUT 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTPS_RETRANSMIT_TIMEOUT {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Parameter TFTPS_RETRIES 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTPS_RETRIES {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Parameter TFTP_CFGFILE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTP_CFGFILE {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Parameter TFTPS_DELAYEDSTART 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTPS_DELAYEDSTART {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Parameter TFTPS_TASK_PRIORITY 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTPS_TASK_PRIORITY {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 Parameter TFTPS_DEBUG_ENABLE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
Parameter	TFTPS_DEBUG_ENABLE {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}


/*********************************
 SubProject TFTP_CFGFILE_EXAMPLE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf 
**********************************/
SubProject	TFTP_CFGFILE_EXAMPLE {
		LAYER += Layer::IPNET_TFTP
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7/cdf/02comp_ipnet_appl_tftp.cdf}
}
