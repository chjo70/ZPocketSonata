/* 00comp_secHash.cdf - secHash components configuration file */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
04mar16,m_c  Fixed name of FOLDER_SEC_HASH and related components
08dec15,rb0  Removed components related to test.
10dec14,rbo  Created.
*/

Folder FOLDER_SEC_HASH {
       NAME	  Hash algorithms
       SYNOPSIS	  VxWorks has a hash API. This folder holds the components to configure what algorithms to include.
       _CHILDREN  FOLDER_SECURITY
       CHILDREN	  FOLDER_SEC_HASH_PROVIDERS \
           INCLUDE_SEC_HASH_MD5 \
           INCLUDE_SEC_HASH_RMD \
           INCLUDE_SEC_HASH_SHA1 \
           INCLUDE_SEC_HASH_SHA256 \
           INCLUDE_SEC_HASH_SHA384 \
           INCLUDE_SEC_HASH_SHA512 \
           INCLUDE_SEC_HASH_WHIRLPOOL
}

Folder FOLDER_SEC_HASH_PROVIDERS {
       NAME	  Providers
       SYNOPSIS	  VxWorks has a hash API. This folder holds the components to configure what providers of included algorithms to include.
       CHILDREN	  SELECT_SEC_HASH_MD5_IMPL \
       	          SELECT_SEC_HASH_RMD_IMPL \
		  SELECT_SEC_HASH_SHA1_IMPL \
		  SELECT_SEC_HASH_SHA256_IMPL \
		  SELECT_SEC_HASH_SHA384_IMPL \
		  SELECT_SEC_HASH_SHA512_IMPL \
		  SELECT_SEC_HASH_WHIRLPOOL_IMPL
}

InitGroup usrSecHashInit {
	  SYNOPSIS	Initialize the secHash providers
	  INIT_RTN   	usrSecHashInit ();
	  INIT_ORDER 	INCLUDE_SEC_HASH_MD5_OPENSSL \
	  		INCLUDE_SEC_HASH_MD5_OPENSSL_EVP \
	  		INCLUDE_SEC_HASH_RMD_OPENSSL \
	  		INCLUDE_SEC_HASH_RMD_OPENSSL_EVP \
	  		INCLUDE_SEC_HASH_SHA1_OPENSSL \
	  		INCLUDE_SEC_HASH_SHA1_OPENSSL_EVP \
	  		INCLUDE_SEC_HASH_SHA256_OPENSSL \
	  		INCLUDE_SEC_HASH_SHA256_OPENSSL_EVP \
	  		INCLUDE_SEC_HASH_SHA384_OPENSSL \
	  		INCLUDE_SEC_HASH_SHA384_OPENSSL_EVP \
	  		INCLUDE_SEC_HASH_SHA512_OPENSSL \
	  		INCLUDE_SEC_HASH_SHA512_OPENSSL_EVP \
	  		INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL \
	  		INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL_EVP
	  _INIT_ORDER	usrRoot
	  INIT_BEFORE   usrKernelExtraInit usrNetworkInit0
}

Component INCLUDE_SEC_HASH_MD5 {
        NAME            MD5
        SYNOPSIS        Includes the secHash MD5 API and installs a configurable \
			MD5 provider
	MODULES		secHashMd5.o
	REQUIRES	SELECT_SEC_HASH_MD5_IMPL
}

Component INCLUDE_SEC_HASH_MD5_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an MD5 provider for the secHash MD5 API. \
			The implementation is based on the low-level openssl APIs. \
			This provider does not require the full openssl lib to be linked in.
	MODULES		secHashMd5Openssl.o
	PROTOTYPE	void secHashMd5OpensslInit(void);
        INIT_RTN        secHashMd5OpensslInit();
}

Component INCLUDE_SEC_HASH_MD5_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an MD5 provider for the secHash MD5 API. \
			The implementation is based on the openssl EVP API. \
			This MD5 provider is required when openssl is built in \
			FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashMd5OpensslEvpInit(void);
        INIT_RTN        secHashMd5OpensslEvpInit();
}

Selection SELECT_SEC_HASH_MD5_IMPL {
        NAME            MD5
        SYNOPSIS        Specifies whether the MD5 provider for the secHash MD5 API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.
        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_MD5_OPENSSL_EVP \
			INCLUDE_SEC_HASH_MD5_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_MD5_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_MD5_OPENSSL
#endif
}

Component INCLUDE_SEC_HASH_RMD {
        NAME            RIPEMD
        SYNOPSIS        Includes the secHash RIPEMD API and installs a configurable \
			RIPEMD provider
	MODULES		secHashRmd.o
	REQUIRES	SELECT_SEC_HASH_RMD_IMPL
}

Component INCLUDE_SEC_HASH_RMD_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an RMD provider for the secHash RMD API. \
			The implementation is based on the low-level openssl APIs. \
			This provider does not require the full openssl lib to be linked in.
	MODULES		secHashRmdOpenssl.o
	PROTOTYPE	void secHashRmdOpensslInit(void);
        INIT_RTN        secHashRmdOpensslInit();
}

Component INCLUDE_SEC_HASH_RMD_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an RMD provider for the secHash RMD API. \
			The implementation is based on the openssl EVP API. \
			This RMD provider is required when openssl is built in \
			FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashRmdOpensslEvpInit(void);
        INIT_RTN        secHashRmdOpensslEvpInit();
}

Selection SELECT_SEC_HASH_RMD_IMPL {
        NAME            RIPEMD
        SYNOPSIS        Specifies whether the RMD provider for the secHash RMD API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.
        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_RMD_OPENSSL_EVP \
			INCLUDE_SEC_HASH_RMD_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_RMD_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_RMD_OPENSSL
#endif

}


Component INCLUDE_SEC_HASH_SHA1 {
        NAME            SHA1
        SYNOPSIS        Includes the secHash SHA1 API and installs a configurable \
			SHA1 provider.
	MODULES		secHashSha1.o
	REQUIRES	SELECT_SEC_HASH_SHA1_IMPL
}

Component INCLUDE_SEC_HASH_SHA1_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an SHA1 provider for the secHash SHA1 API. \
				The implementation is based on the low-level openssl APIs. \
				This provider does not require the full openssl lib to be linked in.
	MODULES		secHashSha1Openssl.o
	PROTOTYPE	void secHashSha1OpensslInit(void);
        INIT_RTN        secHashSha1OpensslInit();
}

Component INCLUDE_SEC_HASH_SHA1_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an SHA1 provider for the secHash SHA1 API. \
				The implementation is based on the openssl EVP API. \
				This SHA1 provider is required when openssl is built in \
				FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashSha1OpensslEvpInit(void);
        INIT_RTN        secHashSha1OpensslEvpInit();
}

Selection SELECT_SEC_HASH_SHA1_IMPL {
        NAME            SHA1
        SYNOPSIS        Specifies whether the SHA1 provider for the secHash SHA1 API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.
        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_SHA1_OPENSSL_EVP \
			INCLUDE_SEC_HASH_SHA1_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_SHA1_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_SHA1_OPENSSL
#endif
}

Component INCLUDE_SEC_HASH_SHA256 {
        NAME            SHA256
        SYNOPSIS        Includes the secHash SHA256 API and installs a configurable \
			SHA256 provider.
	MODULES		secHashSha256.o
	REQUIRES	SELECT_SEC_HASH_SHA256_IMPL
}

Component INCLUDE_SEC_HASH_SHA256_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an SHA256 provider for the secHash SHA256 API. \
			The implementation is based on the low-level openssl APIs. \
			This provider does not require the full openssl lib to be linked in.
	MODULES		secHashSha256Openssl.o
	PROTOTYPE	void secHashSha256OpensslInit(void);
        INIT_RTN        secHashSha256OpensslInit();
}

Component INCLUDE_SEC_HASH_SHA256_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an SHA256 provider for the secHash SHA256 API. \
			The implementation is based on the openssl EVP API. \
			This SHA256 provider is required when openssl is built in \
			FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashSha256OpensslEvpInit(void);
        INIT_RTN        secHashSha256OpensslEvpInit();
}

Selection SELECT_SEC_HASH_SHA256_IMPL {
        NAME            SHA256
        SYNOPSIS        Specifies whether the SHA256 provider for the secHash SHA256 API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.
        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_SHA256_OPENSSL_EVP \
			INCLUDE_SEC_HASH_SHA256_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_SHA256_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_SHA256_OPENSSL
#endif
}

Component INCLUDE_SEC_HASH_SHA384 {
        NAME            SHA384
        SYNOPSIS        Includes the secHash SHA384 API and installs a configurable \
			SHA384 provider
	MODULES		secHashSha384.o
	REQUIRES	SELECT_SEC_HASH_SHA384_IMPL
}

Component INCLUDE_SEC_HASH_SHA384_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an SHA384 provider for the secHash SHA384 API. \
			The implementation is based on the low-level openssl APIs. \
			This provider does not require the full openssl lib to be linked in.
	MODULES		secHashSha384Openssl.o
	PROTOTYPE	void secHashSha384OpensslInit(void);
        INIT_RTN        secHashSha384OpensslInit();
}

Component INCLUDE_SEC_HASH_SHA384_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an SHA384 provider for the secHash SHA384 API. \
			The implementation is based on the openssl EVP API. \
			This SHA384 provider is required when openssl is built in \
			FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashSha384OpensslEvpInit(void);
        INIT_RTN        secHashSha384OpensslEvpInit();
}

Selection SELECT_SEC_HASH_SHA384_IMPL {
        NAME            SHA384
        SYNOPSIS        Specifies whether the SHA384 provider for the secHash SHA384 API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.
        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_SHA384_OPENSSL_EVP \
			INCLUDE_SEC_HASH_SHA384_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_SHA384_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_SHA384_OPENSSL
#endif
}

Component INCLUDE_SEC_HASH_SHA512 {
        NAME            SHA512
        SYNOPSIS        Includes the secHash SHA512 API and installs a configurable \
			SHA512 provider
	MODULES		secHashSha512.o
	REQUIRES	SELECT_SEC_HASH_SHA512_IMPL
}

Component INCLUDE_SEC_HASH_SHA512_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an SHA512 provider for the secHash SHA512 API. \
			The implementation is based on the low-level openssl APIs. \
			This provider does not require the full openssl lib to be linked in.
	MODULES		secHashSha512Openssl.o
	PROTOTYPE	void secHashSha512OpensslInit(void);
        INIT_RTN        secHashSha512OpensslInit();
}

Component INCLUDE_SEC_HASH_SHA512_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an SHA512 provider for the secHash SHA512 API. \
			The implementation is based on the openssl EVP API. \
			This SHA512 provider is required when openssl is built in \
			FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashSha512OpensslEvpInit(void);
        INIT_RTN        secHashSha512OpensslEvpInit();
}

Selection SELECT_SEC_HASH_SHA512_IMPL {
        NAME            SHA512
        SYNOPSIS        Specifies whether the SHA512 provider for the secHash SHA512 API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.

        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_SHA512_OPENSSL_EVP \
			INCLUDE_SEC_HASH_SHA512_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_SHA512_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_SHA512_OPENSSL
#endif
}


Component INCLUDE_SEC_HASH_WHIRLPOOL {
        NAME            Whirlpool
        SYNOPSIS        Includes the secHash Whirlpool API and installs a configurable \
			WHIRLPOOL provider
	MODULES		secHashWhirlpool.o
	REQUIRES	SELECT_SEC_HASH_WHIRLPOOL_IMPL
}

Component INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL {
        NAME            OpenSSL
        SYNOPSIS        Registers an WHIRLPOOL provider for the secHash Whirlpool API. \
			The implementation is based on the low-level openssl APIs. \
			This provider does not require the full openssl lib to be linked in.
	MODULES		secHashWhirlpoolOpenssl.o
	PROTOTYPE	void secHashWhirlpoolOpensslInit(void);
        INIT_RTN        secHashWhirlpoolOpensslInit();
}

Component INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL_EVP {
        NAME            OpenSSL EVP
        SYNOPSIS        Registers an Whirlpool provider for the secHash Whirlpool API. \
			The implementation is based on the openssl EVP API. \
			This Whirlpool provider is required when openssl is built in \
			FIPS 140-2 mode.
	MODULES		secHashOpensslEvp.o
	PROTOTYPE	void secHashWhirlpoolOpensslEvpInit(void);
        INIT_RTN        secHashWhirlpoolOpensslEvpInit();
}

Selection SELECT_SEC_HASH_WHIRLPOOL_IMPL {
        NAME            Whirlpool
        SYNOPSIS        Specifies whether the Whirlpool provider for the secHash Whirpool API \
				will be implemented based on the low-level OpenSSL APIs or the \
				OpenSSL EVP API. By default, it is based on low-level OpenSSL APIS.

        COUNT           1-1
        CHILDREN        INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL_EVP \
			INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL
#ifdef _WRS_CONFIG_OPENSSL_FIPS
        DEFAULTS        INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL_EVP
#else
        DEFAULTS        INCLUDE_SEC_HASH_WHIRLPOOL_OPENSSL
#endif
}

