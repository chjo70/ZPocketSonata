

/* this file is automatically generated */


Layer Layer::ZLIB {
}




/*********************************
 Component INCLUDE_ZLIB 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf 
**********************************/
Component	INCLUDE_ZLIB {
		LAYER += Layer::ZLIB
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf}
}


/*********************************
 Component INCLUDE_ZLIB_DEFLATE 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf 
**********************************/
Component	INCLUDE_ZLIB_DEFLATE {
		LAYER += Layer::ZLIB
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf}
}


/*********************************
 Component INCLUDE_ZLIB_INFLATE 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf 
**********************************/
Component	INCLUDE_ZLIB_INFLATE {
		LAYER += Layer::ZLIB
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf}
}


/*********************************
 Folder FOLDER_ZLIB 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf 
**********************************/
Folder	FOLDER_ZLIB {
		LAYER += Layer::ZLIB
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/utils/zlib-1.2.8.6/cdf/zlib.cdf}
}


/*********************************
 Layer Layer::ZLIB 
 original object sources located at 
 $(VSB_DIR) 
**********************************/
Layer	Layer::ZLIB {
		LAYER += Layer::ZLIB
		LAYER_SOURCE		{$(VSB_DIR)}
}
