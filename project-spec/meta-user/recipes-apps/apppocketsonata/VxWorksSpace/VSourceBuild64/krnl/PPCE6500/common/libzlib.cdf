Symbol adler32 {
}
Symbol .TOC. {
}
Symbol adler32_combine {
}
Symbol adler32_combine64 {
}
Symbol compress2 {
}
Symbol deflateInit_ {
}
Symbol deflate {
}
Symbol deflateEnd {
}
Symbol compress {
}
Symbol compressBound {
}
Symbol get_crc_table {
}
Symbol crc32 {
}
Symbol crc32_combine {
}
Symbol crc32_combine64 {
}
Symbol deflateResetKeep {
}
Symbol _tr_init {
}
Symbol memset {
}
Symbol deflateReset {
}
Symbol deflateInit2_ {
}
Symbol zcalloc {
}
Symbol zcfree {
}
Symbol z_errmsg {
}
Symbol memcpy {
}
Symbol deflateSetDictionary {
}
Symbol deflateSetHeader {
}
Symbol deflatePending {
}
Symbol deflatePrime {
}
Symbol _tr_flush_bits {
}
Symbol _length_code {
}
Symbol _dist_code {
}
Symbol _tr_flush_block {
}
Symbol _tr_align {
}
Symbol _tr_stored_block {
}
Symbol deflateParams {
}
Symbol deflateTune {
}
Symbol deflateBound {
}
Symbol deflateCopy {
}
Symbol deflate_copyright {
}
Symbol gzclose {
}
Symbol gzclose_r {
}
Symbol gzclose_w {
}
Symbol gz_error {
}
Symbol free {
}
Symbol strlen {
}
Symbol malloc {
}
Symbol snprintf {
}
Symbol open {
}
Symbol lseek {
}
Symbol gzopen {
}
Symbol gzopen64 {
}
Symbol gzdopen {
}
Symbol gzbuffer {
}
Symbol gzrewind {
}
Symbol gzseek64 {
}
Symbol gzseek {
}
Symbol gztell64 {
}
Symbol gztell {
}
Symbol gzoffset64 {
}
Symbol gzoffset {
}
Symbol gzeof {
}
Symbol gzerror {
}
Symbol gzclearerr {
}
Symbol read {
}
Symbol __errno {
}
Symbol strerror {
}
Symbol inflateInit2_ {
}
Symbol inflateReset {
}
Symbol inflate {
}
Symbol gzread {
}
Symbol gzgetc {
}
Symbol gzgetc_ {
}
Symbol gzungetc {
}
Symbol gzgets {
}
Symbol memchr {
}
Symbol gzdirect {
}
Symbol inflateEnd {
}
Symbol close {
}
Symbol write {
}
Symbol gzwrite {
}
Symbol gzputc {
}
Symbol gzputs {
}
Symbol gzvprintf {
}
Symbol vsnprintf {
}
Symbol gzprintf {
}
Symbol gzflush {
}
Symbol gzsetparams {
}
Symbol inflateBackInit_ {
}
Symbol inflateBack {
}
Symbol inflate_table {
}
Symbol inflate_fast {
}
Symbol inflateBackEnd {
}
Symbol inflateResetKeep {
}
Symbol inflateReset2 {
}
Symbol inflateInit_ {
}
Symbol inflatePrime {
}
Symbol inflateGetDictionary {
}
Symbol inflateSetDictionary {
}
Symbol inflateGetHeader {
}
Symbol inflateSync {
}
Symbol inflateSyncPoint {
}
Symbol inflateCopy {
}
Symbol inflateUndermine {
}
Symbol inflateMark {
}
Symbol inflate_copyright {
}
Symbol _tr_tally {
}
Symbol uncompress {
}
Symbol zlibVersion {
}
Symbol zlibCompileFlags {
}
Symbol zError {
}
ObjectFile libzlib.a::adler32.o {
	NAME Object file adler32.o from archive libzlib.a
	EXPORTS adler32 adler32_combine adler32_combine64
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module adler32.o {
	OBJECT += libzlib.a::adler32.o
}
ObjectFile libzlib.a::compress.o {
	NAME Object file compress.o from archive libzlib.a
	EXPORTS compress2 compress compressBound
	IMPORTS .TOC. deflateInit_ deflate deflateEnd
	DECLARES 
	USES 
}
Module compress.o {
	OBJECT += libzlib.a::compress.o
}
ObjectFile libzlib.a::crc32.o {
	NAME Object file crc32.o from archive libzlib.a
	EXPORTS get_crc_table crc32 crc32_combine crc32_combine64
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module crc32.o {
	OBJECT += libzlib.a::crc32.o
}
ObjectFile libzlib.a::deflate.o {
	NAME Object file deflate.o from archive libzlib.a
	EXPORTS deflateResetKeep deflateReset deflateEnd deflateInit2_ deflateInit_ deflateSetDictionary deflateSetHeader deflatePending deflatePrime deflate deflateParams deflateTune deflateBound deflateCopy deflate_copyright
	IMPORTS .TOC. crc32 adler32 _tr_init memset zcalloc zcfree z_errmsg memcpy _tr_flush_bits _length_code _dist_code _tr_flush_block _tr_align _tr_stored_block
	DECLARES 
	USES 
}
Module deflate.o {
	OBJECT += libzlib.a::deflate.o
}
ObjectFile libzlib.a::gzclose.o {
	NAME Object file gzclose.o from archive libzlib.a
	EXPORTS gzclose
	IMPORTS .TOC. gzclose_r gzclose_w
	DECLARES 
	USES 
}
Module gzclose.o {
	OBJECT += libzlib.a::gzclose.o
}
ObjectFile libzlib.a::gzlib.o {
	NAME Object file gzlib.o from archive libzlib.a
	EXPORTS gz_error gzopen gzopen64 gzdopen gzbuffer gzrewind gzseek64 gzseek gztell64 gztell gzoffset64 gzoffset gzeof gzerror gzclearerr
	IMPORTS .TOC. free strlen malloc snprintf open lseek
	DECLARES 
	USES 
}
Module gzlib.o {
	OBJECT += libzlib.a::gzlib.o
}
ObjectFile libzlib.a::gzread.o {
	NAME Object file gzread.o from archive libzlib.a
	EXPORTS gzread gzgetc gzgetc_ gzungetc gzgets gzdirect gzclose_r
	IMPORTS .TOC. read __errno strerror gz_error malloc free inflateInit2_ inflateReset memcpy inflate memchr inflateEnd close
	DECLARES 
	USES 
}
Module gzread.o {
	OBJECT += libzlib.a::gzread.o
}
ObjectFile libzlib.a::gzwrite.o {
	NAME Object file gzwrite.o from archive libzlib.a
	EXPORTS gzwrite gzputc gzputs gzvprintf gzprintf gzflush gzsetparams gzclose_w
	IMPORTS .TOC. malloc deflateInit2_ free gz_error write __errno strerror deflate deflateReset memset memcpy strlen vsnprintf deflateParams deflateEnd close
	DECLARES 
	USES 
}
Module gzwrite.o {
	OBJECT += libzlib.a::gzwrite.o
}
ObjectFile libzlib.a::infback.o {
	NAME Object file infback.o from archive libzlib.a
	EXPORTS inflateBackInit_ inflateBack inflateBackEnd
	IMPORTS .TOC. zcalloc zcfree memcpy inflate_table inflate_fast
	DECLARES 
	USES 
}
Module infback.o {
	OBJECT += libzlib.a::infback.o
}
ObjectFile libzlib.a::inffast.o {
	NAME Object file inffast.o from archive libzlib.a
	EXPORTS inflate_fast
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module inffast.o {
	OBJECT += libzlib.a::inffast.o
}
ObjectFile libzlib.a::inflate.o {
	NAME Object file inflate.o from archive libzlib.a
	EXPORTS inflateResetKeep inflateReset inflateReset2 inflateInit2_ inflateInit_ inflatePrime inflate inflateEnd inflateGetDictionary inflateSetDictionary inflateGetHeader inflateSync inflateSyncPoint inflateCopy inflateUndermine inflateMark
	IMPORTS .TOC. zcalloc zcfree memcpy crc32 adler32 inflate_table inflate_fast
	DECLARES 
	USES 
}
Module inflate.o {
	OBJECT += libzlib.a::inflate.o
}
ObjectFile libzlib.a::inftrees.o {
	NAME Object file inftrees.o from archive libzlib.a
	EXPORTS inflate_table inflate_copyright
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module inftrees.o {
	OBJECT += libzlib.a::inftrees.o
}
ObjectFile libzlib.a::trees.o {
	NAME Object file trees.o from archive libzlib.a
	EXPORTS _tr_init _tr_stored_block _tr_flush_bits _tr_align _length_code _dist_code _tr_flush_block _tr_tally
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module trees.o {
	OBJECT += libzlib.a::trees.o
}
ObjectFile libzlib.a::uncompr.o {
	NAME Object file uncompr.o from archive libzlib.a
	EXPORTS uncompress
	IMPORTS .TOC. inflateInit_ inflate inflateEnd
	DECLARES 
	USES 
}
Module uncompr.o {
	OBJECT += libzlib.a::uncompr.o
}
ObjectFile libzlib.a::zutil.o {
	NAME Object file zutil.o from archive libzlib.a
	EXPORTS zlibVersion zlibCompileFlags zError z_errmsg zcalloc zcfree
	IMPORTS .TOC. malloc free
	DECLARES 
	USES 
}
Module zutil.o {
	OBJECT += libzlib.a::zutil.o
}
Library libzlib.a {
	MODULES libzlib.a::adler32.o libzlib.a::compress.o libzlib.a::crc32.o libzlib.a::deflate.o libzlib.a::gzclose.o libzlib.a::gzlib.o libzlib.a::gzread.o libzlib.a::gzwrite.o libzlib.a::infback.o libzlib.a::inffast.o libzlib.a::inflate.o libzlib.a::inftrees.o libzlib.a::trees.o libzlib.a::uncompr.o libzlib.a::zutil.o
}
Symbol adler32 {
}
Symbol .TOC. {
}
Symbol adler32_combine {
}
Symbol adler32_combine64 {
}
Symbol compress2 {
}
Symbol deflateInit_ {
}
Symbol deflate {
}
Symbol deflateEnd {
}
Symbol compress {
}
Symbol compressBound {
}
Symbol get_crc_table {
}
Symbol crc32 {
}
Symbol crc32_combine {
}
Symbol crc32_combine64 {
}
Symbol deflateResetKeep {
}
Symbol _tr_init {
}
Symbol memset {
}
Symbol deflateReset {
}
Symbol deflateInit2_ {
}
Symbol zcalloc {
}
Symbol zcfree {
}
Symbol z_errmsg {
}
Symbol memcpy {
}
Symbol deflateSetDictionary {
}
Symbol deflateSetHeader {
}
Symbol deflatePending {
}
Symbol deflatePrime {
}
Symbol _tr_flush_bits {
}
Symbol _length_code {
}
Symbol _dist_code {
}
Symbol _tr_flush_block {
}
Symbol _tr_align {
}
Symbol _tr_stored_block {
}
Symbol deflateParams {
}
Symbol deflateTune {
}
Symbol deflateBound {
}
Symbol deflateCopy {
}
Symbol deflate_copyright {
}
Symbol gzclose {
}
Symbol gzclose_r {
}
Symbol gzclose_w {
}
Symbol gz_error {
}
Symbol free {
}
Symbol strlen {
}
Symbol malloc {
}
Symbol snprintf {
}
Symbol open {
}
Symbol lseek {
}
Symbol gzopen {
}
Symbol gzopen64 {
}
Symbol gzdopen {
}
Symbol gzbuffer {
}
Symbol gzrewind {
}
Symbol gzseek64 {
}
Symbol gzseek {
}
Symbol gztell64 {
}
Symbol gztell {
}
Symbol gzoffset64 {
}
Symbol gzoffset {
}
Symbol gzeof {
}
Symbol gzerror {
}
Symbol gzclearerr {
}
Symbol read {
}
Symbol __errno {
}
Symbol strerror {
}
Symbol inflateInit2_ {
}
Symbol inflateReset {
}
Symbol inflate {
}
Symbol gzread {
}
Symbol gzgetc {
}
Symbol gzgetc_ {
}
Symbol gzungetc {
}
Symbol gzgets {
}
Symbol memchr {
}
Symbol gzdirect {
}
Symbol inflateEnd {
}
Symbol close {
}
Symbol write {
}
Symbol gzwrite {
}
Symbol gzputc {
}
Symbol gzputs {
}
Symbol gzvprintf {
}
Symbol vsnprintf {
}
Symbol gzprintf {
}
Symbol gzflush {
}
Symbol gzsetparams {
}
Symbol inflateBackInit_ {
}
Symbol inflateBack {
}
Symbol inflate_table {
}
Symbol inflate_fast {
}
Symbol inflateBackEnd {
}
Symbol inflateResetKeep {
}
Symbol inflateReset2 {
}
Symbol inflateInit_ {
}
Symbol inflatePrime {
}
Symbol inflateGetDictionary {
}
Symbol inflateSetDictionary {
}
Symbol inflateGetHeader {
}
Symbol inflateSync {
}
Symbol inflateSyncPoint {
}
Symbol inflateCopy {
}
Symbol inflateUndermine {
}
Symbol inflateMark {
}
Symbol inflate_copyright {
}
Symbol _tr_tally {
}
Symbol uncompress {
}
Symbol zlibVersion {
}
Symbol zlibCompileFlags {
}
Symbol zError {
}
ObjectFile libzlib.a::adler32.o {
	NAME Object file adler32.o from archive libzlib.a
	EXPORTS adler32 adler32_combine adler32_combine64
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module adler32.o {
	OBJECT += libzlib.a::adler32.o
}
ObjectFile libzlib.a::compress.o {
	NAME Object file compress.o from archive libzlib.a
	EXPORTS compress2 compress compressBound
	IMPORTS .TOC. deflateInit_ deflate deflateEnd
	DECLARES 
	USES 
}
Module compress.o {
	OBJECT += libzlib.a::compress.o
}
ObjectFile libzlib.a::crc32.o {
	NAME Object file crc32.o from archive libzlib.a
	EXPORTS get_crc_table crc32 crc32_combine crc32_combine64
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module crc32.o {
	OBJECT += libzlib.a::crc32.o
}
ObjectFile libzlib.a::deflate.o {
	NAME Object file deflate.o from archive libzlib.a
	EXPORTS deflateResetKeep deflateReset deflateEnd deflateInit2_ deflateInit_ deflateSetDictionary deflateSetHeader deflatePending deflatePrime deflate deflateParams deflateTune deflateBound deflateCopy deflate_copyright
	IMPORTS .TOC. crc32 adler32 _tr_init memset zcalloc zcfree z_errmsg memcpy _tr_flush_bits _length_code _dist_code _tr_flush_block _tr_align _tr_stored_block
	DECLARES 
	USES 
}
Module deflate.o {
	OBJECT += libzlib.a::deflate.o
}
ObjectFile libzlib.a::gzclose.o {
	NAME Object file gzclose.o from archive libzlib.a
	EXPORTS gzclose
	IMPORTS .TOC. gzclose_r gzclose_w
	DECLARES 
	USES 
}
Module gzclose.o {
	OBJECT += libzlib.a::gzclose.o
}
ObjectFile libzlib.a::gzlib.o {
	NAME Object file gzlib.o from archive libzlib.a
	EXPORTS gz_error gzopen gzopen64 gzdopen gzbuffer gzrewind gzseek64 gzseek gztell64 gztell gzoffset64 gzoffset gzeof gzerror gzclearerr
	IMPORTS .TOC. free strlen malloc snprintf open lseek
	DECLARES 
	USES 
}
Module gzlib.o {
	OBJECT += libzlib.a::gzlib.o
}
ObjectFile libzlib.a::gzread.o {
	NAME Object file gzread.o from archive libzlib.a
	EXPORTS gzread gzgetc gzgetc_ gzungetc gzgets gzdirect gzclose_r
	IMPORTS .TOC. read __errno strerror gz_error malloc free inflateInit2_ inflateReset memcpy inflate memchr inflateEnd close
	DECLARES 
	USES 
}
Module gzread.o {
	OBJECT += libzlib.a::gzread.o
}
ObjectFile libzlib.a::gzwrite.o {
	NAME Object file gzwrite.o from archive libzlib.a
	EXPORTS gzwrite gzputc gzputs gzvprintf gzprintf gzflush gzsetparams gzclose_w
	IMPORTS .TOC. malloc deflateInit2_ free gz_error write __errno strerror deflate deflateReset memset memcpy strlen vsnprintf deflateParams deflateEnd close
	DECLARES 
	USES 
}
Module gzwrite.o {
	OBJECT += libzlib.a::gzwrite.o
}
ObjectFile libzlib.a::infback.o {
	NAME Object file infback.o from archive libzlib.a
	EXPORTS inflateBackInit_ inflateBack inflateBackEnd
	IMPORTS .TOC. zcalloc zcfree memcpy inflate_table inflate_fast
	DECLARES 
	USES 
}
Module infback.o {
	OBJECT += libzlib.a::infback.o
}
ObjectFile libzlib.a::inffast.o {
	NAME Object file inffast.o from archive libzlib.a
	EXPORTS inflate_fast
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module inffast.o {
	OBJECT += libzlib.a::inffast.o
}
ObjectFile libzlib.a::inflate.o {
	NAME Object file inflate.o from archive libzlib.a
	EXPORTS inflateResetKeep inflateReset inflateReset2 inflateInit2_ inflateInit_ inflatePrime inflate inflateEnd inflateGetDictionary inflateSetDictionary inflateGetHeader inflateSync inflateSyncPoint inflateCopy inflateUndermine inflateMark
	IMPORTS .TOC. zcalloc zcfree memcpy crc32 adler32 inflate_table inflate_fast
	DECLARES 
	USES 
}
Module inflate.o {
	OBJECT += libzlib.a::inflate.o
}
ObjectFile libzlib.a::inftrees.o {
	NAME Object file inftrees.o from archive libzlib.a
	EXPORTS inflate_table inflate_copyright
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module inftrees.o {
	OBJECT += libzlib.a::inftrees.o
}
ObjectFile libzlib.a::trees.o {
	NAME Object file trees.o from archive libzlib.a
	EXPORTS _tr_init _tr_stored_block _tr_flush_bits _tr_align _length_code _dist_code _tr_flush_block _tr_tally
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module trees.o {
	OBJECT += libzlib.a::trees.o
}
ObjectFile libzlib.a::uncompr.o {
	NAME Object file uncompr.o from archive libzlib.a
	EXPORTS uncompress
	IMPORTS .TOC. inflateInit_ inflate inflateEnd
	DECLARES 
	USES 
}
Module uncompr.o {
	OBJECT += libzlib.a::uncompr.o
}
ObjectFile libzlib.a::zutil.o {
	NAME Object file zutil.o from archive libzlib.a
	EXPORTS zlibVersion zlibCompileFlags zError z_errmsg zcalloc zcfree
	IMPORTS .TOC. malloc free
	DECLARES 
	USES 
}
Module zutil.o {
	OBJECT += libzlib.a::zutil.o
}
Library libzlib.a {
	MODULES libzlib.a::adler32.o libzlib.a::compress.o libzlib.a::crc32.o libzlib.a::deflate.o libzlib.a::gzclose.o libzlib.a::gzlib.o libzlib.a::gzread.o libzlib.a::gzwrite.o libzlib.a::infback.o libzlib.a::inffast.o libzlib.a::inflate.o libzlib.a::inftrees.o libzlib.a::trees.o libzlib.a::uncompr.o libzlib.a::zutil.o
}
Symbol adler32 {
}
Symbol .TOC. {
}
Symbol adler32_combine {
}
Symbol adler32_combine64 {
}
Symbol compress2 {
}
Symbol deflateInit_ {
}
Symbol deflate {
}
Symbol deflateEnd {
}
Symbol compress {
}
Symbol compressBound {
}
Symbol get_crc_table {
}
Symbol crc32 {
}
Symbol crc32_combine {
}
Symbol crc32_combine64 {
}
Symbol deflateResetKeep {
}
Symbol _tr_init {
}
Symbol memset {
}
Symbol deflateReset {
}
Symbol deflateInit2_ {
}
Symbol zcalloc {
}
Symbol zcfree {
}
Symbol z_errmsg {
}
Symbol memcpy {
}
Symbol deflateSetDictionary {
}
Symbol deflateSetHeader {
}
Symbol deflatePending {
}
Symbol deflatePrime {
}
Symbol _tr_flush_bits {
}
Symbol _length_code {
}
Symbol _dist_code {
}
Symbol _tr_flush_block {
}
Symbol _tr_align {
}
Symbol _tr_stored_block {
}
Symbol deflateParams {
}
Symbol deflateTune {
}
Symbol deflateBound {
}
Symbol deflateCopy {
}
Symbol deflate_copyright {
}
Symbol gzclose {
}
Symbol gzclose_r {
}
Symbol gzclose_w {
}
Symbol gz_error {
}
Symbol free {
}
Symbol strlen {
}
Symbol malloc {
}
Symbol snprintf {
}
Symbol open {
}
Symbol lseek {
}
Symbol gzopen {
}
Symbol gzopen64 {
}
Symbol gzdopen {
}
Symbol gzbuffer {
}
Symbol gzrewind {
}
Symbol gzseek64 {
}
Symbol gzseek {
}
Symbol gztell64 {
}
Symbol gztell {
}
Symbol gzoffset64 {
}
Symbol gzoffset {
}
Symbol gzeof {
}
Symbol gzerror {
}
Symbol gzclearerr {
}
Symbol read {
}
Symbol __errno {
}
Symbol strerror {
}
Symbol inflateInit2_ {
}
Symbol inflateReset {
}
Symbol inflate {
}
Symbol gzread {
}
Symbol gzgetc {
}
Symbol gzgetc_ {
}
Symbol gzungetc {
}
Symbol gzgets {
}
Symbol memchr {
}
Symbol gzdirect {
}
Symbol inflateEnd {
}
Symbol close {
}
Symbol write {
}
Symbol gzwrite {
}
Symbol gzputc {
}
Symbol gzputs {
}
Symbol gzvprintf {
}
Symbol vsnprintf {
}
Symbol gzprintf {
}
Symbol gzflush {
}
Symbol gzsetparams {
}
Symbol inflateBackInit_ {
}
Symbol inflateBack {
}
Symbol inflate_table {
}
Symbol inflate_fast {
}
Symbol inflateBackEnd {
}
Symbol inflateResetKeep {
}
Symbol inflateReset2 {
}
Symbol inflateInit_ {
}
Symbol inflatePrime {
}
Symbol inflateGetDictionary {
}
Symbol inflateSetDictionary {
}
Symbol inflateGetHeader {
}
Symbol inflateSync {
}
Symbol inflateSyncPoint {
}
Symbol inflateCopy {
}
Symbol inflateUndermine {
}
Symbol inflateMark {
}
Symbol inflate_copyright {
}
Symbol _tr_tally {
}
Symbol uncompress {
}
Symbol zlibVersion {
}
Symbol zlibCompileFlags {
}
Symbol zError {
}
ObjectFile libzlib.a::adler32.o {
	NAME Object file adler32.o from archive libzlib.a
	EXPORTS adler32 adler32_combine adler32_combine64
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module adler32.o {
	OBJECT += libzlib.a::adler32.o
}
ObjectFile libzlib.a::compress.o {
	NAME Object file compress.o from archive libzlib.a
	EXPORTS compress2 compress compressBound
	IMPORTS .TOC. deflateInit_ deflate deflateEnd
	DECLARES 
	USES 
}
Module compress.o {
	OBJECT += libzlib.a::compress.o
}
ObjectFile libzlib.a::crc32.o {
	NAME Object file crc32.o from archive libzlib.a
	EXPORTS get_crc_table crc32 crc32_combine crc32_combine64
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module crc32.o {
	OBJECT += libzlib.a::crc32.o
}
ObjectFile libzlib.a::deflate.o {
	NAME Object file deflate.o from archive libzlib.a
	EXPORTS deflateResetKeep deflateReset deflateEnd deflateInit2_ deflateInit_ deflateSetDictionary deflateSetHeader deflatePending deflatePrime deflate deflateParams deflateTune deflateBound deflateCopy deflate_copyright
	IMPORTS .TOC. crc32 adler32 _tr_init memset zcalloc zcfree z_errmsg memcpy _tr_flush_bits _length_code _dist_code _tr_flush_block _tr_align _tr_stored_block
	DECLARES 
	USES 
}
Module deflate.o {
	OBJECT += libzlib.a::deflate.o
}
ObjectFile libzlib.a::gzclose.o {
	NAME Object file gzclose.o from archive libzlib.a
	EXPORTS gzclose
	IMPORTS .TOC. gzclose_r gzclose_w
	DECLARES 
	USES 
}
Module gzclose.o {
	OBJECT += libzlib.a::gzclose.o
}
ObjectFile libzlib.a::gzlib.o {
	NAME Object file gzlib.o from archive libzlib.a
	EXPORTS gz_error gzopen gzopen64 gzdopen gzbuffer gzrewind gzseek64 gzseek gztell64 gztell gzoffset64 gzoffset gzeof gzerror gzclearerr
	IMPORTS .TOC. free strlen malloc snprintf open lseek
	DECLARES 
	USES 
}
Module gzlib.o {
	OBJECT += libzlib.a::gzlib.o
}
ObjectFile libzlib.a::gzread.o {
	NAME Object file gzread.o from archive libzlib.a
	EXPORTS gzread gzgetc gzgetc_ gzungetc gzgets gzdirect gzclose_r
	IMPORTS .TOC. read __errno strerror gz_error malloc free inflateInit2_ inflateReset memcpy inflate memchr inflateEnd close
	DECLARES 
	USES 
}
Module gzread.o {
	OBJECT += libzlib.a::gzread.o
}
ObjectFile libzlib.a::gzwrite.o {
	NAME Object file gzwrite.o from archive libzlib.a
	EXPORTS gzwrite gzputc gzputs gzvprintf gzprintf gzflush gzsetparams gzclose_w
	IMPORTS .TOC. malloc deflateInit2_ free gz_error write __errno strerror deflate deflateReset memset memcpy strlen vsnprintf deflateParams deflateEnd close
	DECLARES 
	USES 
}
Module gzwrite.o {
	OBJECT += libzlib.a::gzwrite.o
}
ObjectFile libzlib.a::infback.o {
	NAME Object file infback.o from archive libzlib.a
	EXPORTS inflateBackInit_ inflateBack inflateBackEnd
	IMPORTS .TOC. zcalloc zcfree memcpy inflate_table inflate_fast
	DECLARES 
	USES 
}
Module infback.o {
	OBJECT += libzlib.a::infback.o
}
ObjectFile libzlib.a::inffast.o {
	NAME Object file inffast.o from archive libzlib.a
	EXPORTS inflate_fast
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module inffast.o {
	OBJECT += libzlib.a::inffast.o
}
ObjectFile libzlib.a::inflate.o {
	NAME Object file inflate.o from archive libzlib.a
	EXPORTS inflateResetKeep inflateReset inflateReset2 inflateInit2_ inflateInit_ inflatePrime inflate inflateEnd inflateGetDictionary inflateSetDictionary inflateGetHeader inflateSync inflateSyncPoint inflateCopy inflateUndermine inflateMark
	IMPORTS .TOC. zcalloc zcfree memcpy crc32 adler32 inflate_table inflate_fast
	DECLARES 
	USES 
}
Module inflate.o {
	OBJECT += libzlib.a::inflate.o
}
ObjectFile libzlib.a::inftrees.o {
	NAME Object file inftrees.o from archive libzlib.a
	EXPORTS inflate_table inflate_copyright
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module inftrees.o {
	OBJECT += libzlib.a::inftrees.o
}
ObjectFile libzlib.a::trees.o {
	NAME Object file trees.o from archive libzlib.a
	EXPORTS _tr_init _tr_stored_block _tr_flush_bits _tr_align _length_code _dist_code _tr_flush_block _tr_tally
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module trees.o {
	OBJECT += libzlib.a::trees.o
}
ObjectFile libzlib.a::uncompr.o {
	NAME Object file uncompr.o from archive libzlib.a
	EXPORTS uncompress
	IMPORTS .TOC. inflateInit_ inflate inflateEnd
	DECLARES 
	USES 
}
Module uncompr.o {
	OBJECT += libzlib.a::uncompr.o
}
ObjectFile libzlib.a::zutil.o {
	NAME Object file zutil.o from archive libzlib.a
	EXPORTS zlibVersion zlibCompileFlags zError z_errmsg zcalloc zcfree
	IMPORTS .TOC. malloc free
	DECLARES 
	USES 
}
Module zutil.o {
	OBJECT += libzlib.a::zutil.o
}
Library libzlib.a {
	MODULES libzlib.a::adler32.o libzlib.a::compress.o libzlib.a::crc32.o libzlib.a::deflate.o libzlib.a::gzclose.o libzlib.a::gzlib.o libzlib.a::gzread.o libzlib.a::gzwrite.o libzlib.a::infback.o libzlib.a::inffast.o libzlib.a::inflate.o libzlib.a::inftrees.o libzlib.a::trees.o libzlib.a::uncompr.o libzlib.a::zutil.o
}
