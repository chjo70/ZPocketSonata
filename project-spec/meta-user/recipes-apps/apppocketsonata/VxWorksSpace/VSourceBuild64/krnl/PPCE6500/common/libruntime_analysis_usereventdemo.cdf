Symbol .TOC. {
}
Symbol bzero {
}
Symbol select {
}
Symbol memdemo_fibonacci_example {
}
Symbol mybuf_strdup {
}
Symbol printf {
}
Symbol strlen {
}
Symbol mybuf_alloc {
}
Symbol strncpy {
}
Symbol mybuf_free {
}
Symbol memdemo {
}
Symbol __stdout {
}
Symbol fflush {
}
Symbol malloc {
}
Symbol cafe_user_event_unsigned {
}
Symbol free {
}
Symbol memcpy {
}
ObjectFile libruntime_analysis_usereventdemo.a::memdemo.o {
	NAME Object file memdemo.o from archive libruntime_analysis_usereventdemo.a
	EXPORTS memdemo_fibonacci_example memdemo
	IMPORTS .TOC. bzero select mybuf_strdup printf strlen mybuf_alloc strncpy mybuf_free __stdout fflush
	DECLARES 
	USES 
}
Module memdemo.o {
	OBJECT += libruntime_analysis_usereventdemo.a::memdemo.o
}
ObjectFile libruntime_analysis_usereventdemo.a::mybuffer.o {
	NAME Object file mybuffer.o from archive libruntime_analysis_usereventdemo.a
	EXPORTS mybuf_alloc mybuf_free mybuf_strdup
	IMPORTS .TOC. malloc cafe_user_event_unsigned free strlen memcpy
	DECLARES 
	USES 
}
Module mybuffer.o {
	OBJECT += libruntime_analysis_usereventdemo.a::mybuffer.o
}
Library libruntime_analysis_usereventdemo.a {
	MODULES libruntime_analysis_usereventdemo.a::memdemo.o libruntime_analysis_usereventdemo.a::mybuffer.o
}
Symbol .TOC. {
}
Symbol bzero {
}
Symbol select {
}
Symbol memdemo_fibonacci_example {
}
Symbol mybuf_strdup {
}
Symbol printf {
}
Symbol strlen {
}
Symbol mybuf_alloc {
}
Symbol strncpy {
}
Symbol mybuf_free {
}
Symbol memdemo {
}
Symbol __stdout {
}
Symbol fflush {
}
Symbol malloc {
}
Symbol cafe_user_event_unsigned {
}
Symbol free {
}
Symbol memcpy {
}
ObjectFile libruntime_analysis_usereventdemo.a::memdemo.o {
	NAME Object file memdemo.o from archive libruntime_analysis_usereventdemo.a
	EXPORTS memdemo_fibonacci_example memdemo
	IMPORTS .TOC. bzero select mybuf_strdup printf strlen mybuf_alloc strncpy mybuf_free __stdout fflush
	DECLARES 
	USES 
}
Module memdemo.o {
	OBJECT += libruntime_analysis_usereventdemo.a::memdemo.o
}
ObjectFile libruntime_analysis_usereventdemo.a::mybuffer.o {
	NAME Object file mybuffer.o from archive libruntime_analysis_usereventdemo.a
	EXPORTS mybuf_alloc mybuf_free mybuf_strdup
	IMPORTS .TOC. malloc cafe_user_event_unsigned free strlen memcpy
	DECLARES 
	USES 
}
Module mybuffer.o {
	OBJECT += libruntime_analysis_usereventdemo.a::mybuffer.o
}
Library libruntime_analysis_usereventdemo.a {
	MODULES libruntime_analysis_usereventdemo.a::memdemo.o libruntime_analysis_usereventdemo.a::mybuffer.o
}
Symbol .TOC. {
}
Symbol bzero {
}
Symbol select {
}
Symbol memdemo_fibonacci_example {
}
Symbol mybuf_strdup {
}
Symbol printf {
}
Symbol strlen {
}
Symbol mybuf_alloc {
}
Symbol strncpy {
}
Symbol mybuf_free {
}
Symbol memdemo {
}
Symbol __stdout {
}
Symbol fflush {
}
Symbol malloc {
}
Symbol cafe_user_event_unsigned {
}
Symbol free {
}
Symbol memcpy {
}
ObjectFile libruntime_analysis_usereventdemo.a::memdemo.o {
	NAME Object file memdemo.o from archive libruntime_analysis_usereventdemo.a
	EXPORTS memdemo_fibonacci_example memdemo
	IMPORTS .TOC. bzero select mybuf_strdup printf strlen mybuf_alloc strncpy mybuf_free __stdout fflush
	DECLARES 
	USES 
}
Module memdemo.o {
	OBJECT += libruntime_analysis_usereventdemo.a::memdemo.o
}
ObjectFile libruntime_analysis_usereventdemo.a::mybuffer.o {
	NAME Object file mybuffer.o from archive libruntime_analysis_usereventdemo.a
	EXPORTS mybuf_alloc mybuf_free mybuf_strdup
	IMPORTS .TOC. malloc cafe_user_event_unsigned free strlen memcpy
	DECLARES 
	USES 
}
Module mybuffer.o {
	OBJECT += libruntime_analysis_usereventdemo.a::mybuffer.o
}
Library libruntime_analysis_usereventdemo.a {
	MODULES libruntime_analysis_usereventdemo.a::memdemo.o libruntime_analysis_usereventdemo.a::mybuffer.o
}
