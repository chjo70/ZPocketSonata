

/* this file is automatically generated */


Layer Layer::JOBQUEUE {
}




/*********************************
 Component INCLUDE_JOB_QUEUE 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf 
**********************************/
Component	INCLUDE_JOB_QUEUE {
		LAYER += Layer::JOBQUEUE
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf}
}


/*********************************
 Component INCLUDE_JOB_QUEUE_UTIL 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf 
**********************************/
Component	INCLUDE_JOB_QUEUE_UTIL {
		LAYER += Layer::JOBQUEUE
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf}
}


/*********************************
 Folder FOLDER_JOBQUEUE 
 original object sources located at 
 $(WIND_BASE)/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf 
**********************************/
Folder	FOLDER_JOBQUEUE {
		LAYER += Layer::JOBQUEUE
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf}
}


/*********************************
 Layer Layer::JOBQUEUE 
 original object sources located at 
 $(VSB_DIR) 
**********************************/
Layer	Layer::JOBQUEUE {
		LAYER += Layer::JOBQUEUE
		LAYER_SOURCE		{$(VSB_DIR)}
}
