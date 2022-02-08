

/* this file is automatically generated */


Layer Layer::FS_DEVFS {
}




/*********************************
 Component INCLUDE_RAWFS 
 original object sources located at 
 $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0/cdf/10comp_devfs.cdf 
**********************************/
Component	INCLUDE_RAWFS {
		LAYER += Layer::FS_DEVFS
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0/cdf/10comp_devfs.cdf}
}


/*********************************
 Folder FOLDER_DEVFS 
 original object sources located at 
 $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0/cdf/10comp_devfs.cdf 
**********************************/
Folder	FOLDER_DEVFS {
		LAYER += Layer::FS_DEVFS
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0/cdf/10comp_devfs.cdf}
}


/*********************************
 Layer Layer::FS_DEVFS 
 original object sources located at 
 $(VSB_DIR) 
**********************************/
Layer	Layer::FS_DEVFS {
		LAYER += Layer::FS_DEVFS
		LAYER_SOURCE		{$(VSB_DIR)}
}


/*********************************
 Parameter NUM_RAWFS_FILES 
 original object sources located at 
 $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0/cdf/10comp_devfs.cdf 
**********************************/
Parameter	NUM_RAWFS_FILES {
		LAYER += Layer::FS_DEVFS
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0/cdf/10comp_devfs.cdf}
}
