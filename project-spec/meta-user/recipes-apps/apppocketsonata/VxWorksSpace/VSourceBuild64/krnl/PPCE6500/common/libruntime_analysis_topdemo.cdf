Symbol .TOC. {
}
Symbol open {
}
Symbol vxAtomicGet {
}
Symbol lseek {
}
Symbol write {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol read {
}
Symbol close {
}
Symbol remove {
}
Symbol printf {
}
Symbol vxAtomicSet {
}
Symbol taskCpuAffinitySet {
}
Symbol tickGet {
}
Symbol tree_a {
}
Symbol cafe_demo_load_test_start {
}
Symbol vxCpuConfiguredGet {
}
Symbol snprintf {
}
Symbol taskCreate {
}
Symbol taskActivate {
}
Symbol cafe_demo_load_test_stop {
}
Symbol cafe_demo_load_cycle {
}
Symbol cafe_demo_load_ramp_start {
}
Symbol taskSpawn {
}
Symbol cafe_demo_load_ramp_stop {
}
Symbol malloc {
}
Symbol cafe_goodBadTestResult {
}
Symbol tick64Get {
}
Symbol free {
}
Symbol taskSuspend {
}
Symbol cafe_demo_cache_bad {
}
Symbol cafe_demo_cache_good {
}
Symbol memset {
}
Symbol memPartCreate {
}
Symbol memPartOptionsGet {
}
Symbol memPartOptionsSet {
}
Symbol memPartAlloc {
}
Symbol memPartInfoGet {
}
Symbol memPartFree {
}
Symbol memPartDelete {
}
Symbol memSysPartId {
}
Symbol wdInitialize {
}
Symbol wdStart {
}
Symbol taskClassId {
}
Symbol objVerify {
}
Symbol cafe_demo_task_stop {
}
Symbol cafe_demo_task_start {
}
Symbol rand {
}
Symbol cafe_demo_io_start {
}
Symbol cafe_demo_io_stop {
}
Symbol taskPrioritySet {
}
Symbol cafe_demo_priority_start {
}
Symbol cafe_demo_priority_stop {
}
Symbol cafe_demo_multi_stop {
}
Symbol cafe_demo_multi_start {
}
Symbol intCpuLock {
}
Symbol intCpuUnlock {
}
Symbol cafe_demo_intlock_start {
}
Symbol cafe_demo_intlock_stop {
}
Symbol taskIdSelf {
}
Symbol vxCpuEnabledGet {
}
Symbol cafe_demo_task_mover_start {
}
Symbol cafe_demo_task_mover_stop {
}
Symbol cafe_demo_idletask_start {
}
Symbol cafe_demo_idletask_stop {
}
Symbol cpuLoadTestStart {
}
Symbol cpuLoadTestStop {
}
Symbol cacheTestBad {
}
Symbol cacheTestGood {
}
Symbol topDemoStop {
}
Symbol topDemoStart {
}
Symbol intLockerStart {
}
Symbol intLockerStop {
}
Symbol idleTaskStart {
}
Symbol idleTaskStop {
}
Symbol taskMoverStart {
}
Symbol taskMoverStop {
}
Symbol tree_b {
}
Symbol tree_c {
}
Symbol tree_x {
}
Symbol a_a {
}
Symbol tree_d {
}
Symbol b_b {
}
Symbol c_c {
}
Symbol d_d {
}
Symbol tree_y {
}
Symbol x_x {
}
Symbol y_y {
}
ObjectFile libruntime_analysis_topdemo.a::cafe_top_demo.o {
	NAME Object file cafe_top_demo.o from archive libruntime_analysis_topdemo.a
	EXPORTS cafe_demo_load_test_start cafe_demo_load_test_stop cafe_demo_load_cycle cafe_demo_load_ramp_start cafe_demo_load_ramp_stop cafe_demo_cache_bad cafe_demo_cache_good cafe_demo_task_stop cafe_demo_task_start cafe_demo_io_start cafe_demo_io_stop cafe_demo_priority_start cafe_demo_priority_stop cafe_demo_multi_stop cafe_demo_multi_start cafe_demo_intlock_start cafe_demo_intlock_stop cafe_demo_task_mover_start cafe_demo_task_mover_stop cafe_demo_idletask_start cafe_demo_idletask_stop
	IMPORTS .TOC. open vxAtomicGet lseek write sysClkRateGet taskDelay read close remove printf vxAtomicSet taskCpuAffinitySet tickGet tree_a vxCpuConfiguredGet snprintf taskCreate taskActivate taskSpawn malloc tick64Get free taskSuspend memset memPartCreate memPartOptionsGet memPartOptionsSet memPartAlloc memPartInfoGet memPartFree memPartDelete memSysPartId wdInitialize wdStart taskClassId objVerify rand taskPrioritySet intCpuLock intCpuUnlock taskIdSelf vxCpuEnabledGet
	DECLARES cafe_goodBadTestResult
	USES 
}
Module cafe_top_demo.o {
	OBJECT += libruntime_analysis_topdemo.a::cafe_top_demo.o
}
ObjectFile libruntime_analysis_topdemo.a::topDemoLib.o {
	NAME Object file topDemoLib.o from archive libruntime_analysis_topdemo.a
	EXPORTS cpuLoadTestStart cpuLoadTestStop cacheTestBad cacheTestGood topDemoStop topDemoStart intLockerStart intLockerStop idleTaskStart idleTaskStop taskMoverStart taskMoverStop
	IMPORTS .TOC. cafe_demo_load_test_start cafe_demo_load_test_stop cafe_demo_cache_bad cafe_demo_cache_good cafe_demo_multi_stop cafe_demo_multi_start cafe_demo_intlock_start cafe_demo_intlock_stop cafe_demo_idletask_start cafe_demo_idletask_stop cafe_demo_task_mover_start cafe_demo_task_mover_stop
	DECLARES 
	USES 
}
Module topDemoLib.o {
	OBJECT += libruntime_analysis_topdemo.a::topDemoLib.o
}
ObjectFile libruntime_analysis_topdemo.a::a.o {
	NAME Object file a.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_a
	IMPORTS .TOC. tree_b tree_c tree_x
	DECLARES a_a
	USES 
}
Module a.o {
	OBJECT += libruntime_analysis_topdemo.a::a.o
}
ObjectFile libruntime_analysis_topdemo.a::b.o {
	NAME Object file b.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_b
	IMPORTS .TOC. tree_c tree_d
	DECLARES b_b
	USES 
}
Module b.o {
	OBJECT += libruntime_analysis_topdemo.a::b.o
}
ObjectFile libruntime_analysis_topdemo.a::c.o {
	NAME Object file c.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_c
	IMPORTS .TOC. tree_d
	DECLARES c_c
	USES 
}
Module c.o {
	OBJECT += libruntime_analysis_topdemo.a::c.o
}
ObjectFile libruntime_analysis_topdemo.a::d.o {
	NAME Object file d.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_d
	IMPORTS .TOC.
	DECLARES d_d
	USES 
}
Module d.o {
	OBJECT += libruntime_analysis_topdemo.a::d.o
}
ObjectFile libruntime_analysis_topdemo.a::x.o {
	NAME Object file x.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_x
	IMPORTS .TOC. tree_c tree_y
	DECLARES x_x
	USES 
}
Module x.o {
	OBJECT += libruntime_analysis_topdemo.a::x.o
}
ObjectFile libruntime_analysis_topdemo.a::y.o {
	NAME Object file y.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_y
	IMPORTS .TOC.
	DECLARES y_y
	USES 
}
Module y.o {
	OBJECT += libruntime_analysis_topdemo.a::y.o
}
Library libruntime_analysis_topdemo.a {
	MODULES libruntime_analysis_topdemo.a::cafe_top_demo.o libruntime_analysis_topdemo.a::topDemoLib.o libruntime_analysis_topdemo.a::a.o libruntime_analysis_topdemo.a::b.o libruntime_analysis_topdemo.a::c.o libruntime_analysis_topdemo.a::d.o libruntime_analysis_topdemo.a::x.o libruntime_analysis_topdemo.a::y.o
}
Symbol .TOC. {
}
Symbol open {
}
Symbol vxAtomicGet {
}
Symbol lseek {
}
Symbol write {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol read {
}
Symbol close {
}
Symbol remove {
}
Symbol printf {
}
Symbol vxAtomicSet {
}
Symbol taskCpuAffinitySet {
}
Symbol tickGet {
}
Symbol tree_a {
}
Symbol cafe_demo_load_test_start {
}
Symbol vxCpuConfiguredGet {
}
Symbol snprintf {
}
Symbol taskCreate {
}
Symbol taskActivate {
}
Symbol cafe_demo_load_test_stop {
}
Symbol cafe_demo_load_cycle {
}
Symbol cafe_demo_load_ramp_start {
}
Symbol taskSpawn {
}
Symbol cafe_demo_load_ramp_stop {
}
Symbol malloc {
}
Symbol cafe_goodBadTestResult {
}
Symbol tick64Get {
}
Symbol free {
}
Symbol taskSuspend {
}
Symbol cafe_demo_cache_bad {
}
Symbol cafe_demo_cache_good {
}
Symbol memset {
}
Symbol memPartCreate {
}
Symbol memPartOptionsGet {
}
Symbol memPartOptionsSet {
}
Symbol memPartAlloc {
}
Symbol memPartInfoGet {
}
Symbol memPartFree {
}
Symbol memPartDelete {
}
Symbol memSysPartId {
}
Symbol wdInitialize {
}
Symbol wdStart {
}
Symbol taskClassId {
}
Symbol objVerify {
}
Symbol cafe_demo_task_stop {
}
Symbol cafe_demo_task_start {
}
Symbol rand {
}
Symbol cafe_demo_io_start {
}
Symbol cafe_demo_io_stop {
}
Symbol taskPrioritySet {
}
Symbol cafe_demo_priority_start {
}
Symbol cafe_demo_priority_stop {
}
Symbol cafe_demo_multi_stop {
}
Symbol cafe_demo_multi_start {
}
Symbol intCpuLock {
}
Symbol intCpuUnlock {
}
Symbol cafe_demo_intlock_start {
}
Symbol cafe_demo_intlock_stop {
}
Symbol taskIdSelf {
}
Symbol vxCpuEnabledGet {
}
Symbol cafe_demo_task_mover_start {
}
Symbol cafe_demo_task_mover_stop {
}
Symbol cafe_demo_idletask_start {
}
Symbol cafe_demo_idletask_stop {
}
Symbol cpuLoadTestStart {
}
Symbol cpuLoadTestStop {
}
Symbol cacheTestBad {
}
Symbol cacheTestGood {
}
Symbol topDemoStop {
}
Symbol topDemoStart {
}
Symbol intLockerStart {
}
Symbol intLockerStop {
}
Symbol idleTaskStart {
}
Symbol idleTaskStop {
}
Symbol taskMoverStart {
}
Symbol taskMoverStop {
}
Symbol tree_b {
}
Symbol tree_c {
}
Symbol tree_x {
}
Symbol a_a {
}
Symbol tree_d {
}
Symbol b_b {
}
Symbol c_c {
}
Symbol d_d {
}
Symbol tree_y {
}
Symbol x_x {
}
Symbol y_y {
}
ObjectFile libruntime_analysis_topdemo.a::cafe_top_demo.o {
	NAME Object file cafe_top_demo.o from archive libruntime_analysis_topdemo.a
	EXPORTS cafe_demo_load_test_start cafe_demo_load_test_stop cafe_demo_load_cycle cafe_demo_load_ramp_start cafe_demo_load_ramp_stop cafe_demo_cache_bad cafe_demo_cache_good cafe_demo_task_stop cafe_demo_task_start cafe_demo_io_start cafe_demo_io_stop cafe_demo_priority_start cafe_demo_priority_stop cafe_demo_multi_stop cafe_demo_multi_start cafe_demo_intlock_start cafe_demo_intlock_stop cafe_demo_task_mover_start cafe_demo_task_mover_stop cafe_demo_idletask_start cafe_demo_idletask_stop
	IMPORTS .TOC. open vxAtomicGet lseek write sysClkRateGet taskDelay read close remove printf vxAtomicSet taskCpuAffinitySet tickGet tree_a vxCpuConfiguredGet snprintf taskCreate taskActivate taskSpawn malloc tick64Get free taskSuspend memset memPartCreate memPartOptionsGet memPartOptionsSet memPartAlloc memPartInfoGet memPartFree memPartDelete memSysPartId wdInitialize wdStart taskClassId objVerify rand taskPrioritySet intCpuLock intCpuUnlock taskIdSelf vxCpuEnabledGet
	DECLARES cafe_goodBadTestResult
	USES 
}
Module cafe_top_demo.o {
	OBJECT += libruntime_analysis_topdemo.a::cafe_top_demo.o
}
ObjectFile libruntime_analysis_topdemo.a::topDemoLib.o {
	NAME Object file topDemoLib.o from archive libruntime_analysis_topdemo.a
	EXPORTS cpuLoadTestStart cpuLoadTestStop cacheTestBad cacheTestGood topDemoStop topDemoStart intLockerStart intLockerStop idleTaskStart idleTaskStop taskMoverStart taskMoverStop
	IMPORTS .TOC. cafe_demo_load_test_start cafe_demo_load_test_stop cafe_demo_cache_bad cafe_demo_cache_good cafe_demo_multi_stop cafe_demo_multi_start cafe_demo_intlock_start cafe_demo_intlock_stop cafe_demo_idletask_start cafe_demo_idletask_stop cafe_demo_task_mover_start cafe_demo_task_mover_stop
	DECLARES 
	USES 
}
Module topDemoLib.o {
	OBJECT += libruntime_analysis_topdemo.a::topDemoLib.o
}
ObjectFile libruntime_analysis_topdemo.a::a.o {
	NAME Object file a.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_a
	IMPORTS .TOC. tree_b tree_c tree_x
	DECLARES a_a
	USES 
}
Module a.o {
	OBJECT += libruntime_analysis_topdemo.a::a.o
}
ObjectFile libruntime_analysis_topdemo.a::b.o {
	NAME Object file b.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_b
	IMPORTS .TOC. tree_c tree_d
	DECLARES b_b
	USES 
}
Module b.o {
	OBJECT += libruntime_analysis_topdemo.a::b.o
}
ObjectFile libruntime_analysis_topdemo.a::c.o {
	NAME Object file c.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_c
	IMPORTS .TOC. tree_d
	DECLARES c_c
	USES 
}
Module c.o {
	OBJECT += libruntime_analysis_topdemo.a::c.o
}
ObjectFile libruntime_analysis_topdemo.a::d.o {
	NAME Object file d.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_d
	IMPORTS .TOC.
	DECLARES d_d
	USES 
}
Module d.o {
	OBJECT += libruntime_analysis_topdemo.a::d.o
}
ObjectFile libruntime_analysis_topdemo.a::x.o {
	NAME Object file x.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_x
	IMPORTS .TOC. tree_c tree_y
	DECLARES x_x
	USES 
}
Module x.o {
	OBJECT += libruntime_analysis_topdemo.a::x.o
}
ObjectFile libruntime_analysis_topdemo.a::y.o {
	NAME Object file y.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_y
	IMPORTS .TOC.
	DECLARES y_y
	USES 
}
Module y.o {
	OBJECT += libruntime_analysis_topdemo.a::y.o
}
Library libruntime_analysis_topdemo.a {
	MODULES libruntime_analysis_topdemo.a::cafe_top_demo.o libruntime_analysis_topdemo.a::topDemoLib.o libruntime_analysis_topdemo.a::a.o libruntime_analysis_topdemo.a::b.o libruntime_analysis_topdemo.a::c.o libruntime_analysis_topdemo.a::d.o libruntime_analysis_topdemo.a::x.o libruntime_analysis_topdemo.a::y.o
}
Symbol .TOC. {
}
Symbol open {
}
Symbol vxAtomicGet {
}
Symbol lseek {
}
Symbol write {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol read {
}
Symbol close {
}
Symbol remove {
}
Symbol printf {
}
Symbol vxAtomicSet {
}
Symbol taskCpuAffinitySet {
}
Symbol tickGet {
}
Symbol tree_a {
}
Symbol cafe_demo_load_test_start {
}
Symbol vxCpuConfiguredGet {
}
Symbol snprintf {
}
Symbol taskCreate {
}
Symbol taskActivate {
}
Symbol cafe_demo_load_test_stop {
}
Symbol cafe_demo_load_cycle {
}
Symbol cafe_demo_load_ramp_start {
}
Symbol taskSpawn {
}
Symbol cafe_demo_load_ramp_stop {
}
Symbol malloc {
}
Symbol cafe_goodBadTestResult {
}
Symbol tick64Get {
}
Symbol free {
}
Symbol taskSuspend {
}
Symbol cafe_demo_cache_bad {
}
Symbol cafe_demo_cache_good {
}
Symbol memset {
}
Symbol memPartCreate {
}
Symbol memPartOptionsGet {
}
Symbol memPartOptionsSet {
}
Symbol memPartAlloc {
}
Symbol memPartInfoGet {
}
Symbol memPartFree {
}
Symbol memPartDelete {
}
Symbol memSysPartId {
}
Symbol wdInitialize {
}
Symbol wdStart {
}
Symbol taskClassId {
}
Symbol objVerify {
}
Symbol cafe_demo_task_stop {
}
Symbol cafe_demo_task_start {
}
Symbol rand {
}
Symbol cafe_demo_io_start {
}
Symbol cafe_demo_io_stop {
}
Symbol taskPrioritySet {
}
Symbol cafe_demo_priority_start {
}
Symbol cafe_demo_priority_stop {
}
Symbol cafe_demo_multi_stop {
}
Symbol cafe_demo_multi_start {
}
Symbol intCpuLock {
}
Symbol intCpuUnlock {
}
Symbol cafe_demo_intlock_start {
}
Symbol cafe_demo_intlock_stop {
}
Symbol taskIdSelf {
}
Symbol vxCpuEnabledGet {
}
Symbol cafe_demo_task_mover_start {
}
Symbol cafe_demo_task_mover_stop {
}
Symbol cafe_demo_idletask_start {
}
Symbol cafe_demo_idletask_stop {
}
Symbol cpuLoadTestStart {
}
Symbol cpuLoadTestStop {
}
Symbol cacheTestBad {
}
Symbol cacheTestGood {
}
Symbol topDemoStop {
}
Symbol topDemoStart {
}
Symbol intLockerStart {
}
Symbol intLockerStop {
}
Symbol idleTaskStart {
}
Symbol idleTaskStop {
}
Symbol taskMoverStart {
}
Symbol taskMoverStop {
}
Symbol tree_b {
}
Symbol tree_c {
}
Symbol tree_x {
}
Symbol a_a {
}
Symbol tree_d {
}
Symbol b_b {
}
Symbol c_c {
}
Symbol d_d {
}
Symbol tree_y {
}
Symbol x_x {
}
Symbol y_y {
}
ObjectFile libruntime_analysis_topdemo.a::cafe_top_demo.o {
	NAME Object file cafe_top_demo.o from archive libruntime_analysis_topdemo.a
	EXPORTS cafe_demo_load_test_start cafe_demo_load_test_stop cafe_demo_load_cycle cafe_demo_load_ramp_start cafe_demo_load_ramp_stop cafe_demo_cache_bad cafe_demo_cache_good cafe_demo_task_stop cafe_demo_task_start cafe_demo_io_start cafe_demo_io_stop cafe_demo_priority_start cafe_demo_priority_stop cafe_demo_multi_stop cafe_demo_multi_start cafe_demo_intlock_start cafe_demo_intlock_stop cafe_demo_task_mover_start cafe_demo_task_mover_stop cafe_demo_idletask_start cafe_demo_idletask_stop
	IMPORTS .TOC. open vxAtomicGet lseek write sysClkRateGet taskDelay read close remove printf vxAtomicSet taskCpuAffinitySet tickGet tree_a vxCpuConfiguredGet snprintf taskCreate taskActivate taskSpawn malloc tick64Get free taskSuspend memset memPartCreate memPartOptionsGet memPartOptionsSet memPartAlloc memPartInfoGet memPartFree memPartDelete memSysPartId wdInitialize wdStart taskClassId objVerify rand taskPrioritySet intCpuLock intCpuUnlock taskIdSelf vxCpuEnabledGet
	DECLARES cafe_goodBadTestResult
	USES 
}
Module cafe_top_demo.o {
	OBJECT += libruntime_analysis_topdemo.a::cafe_top_demo.o
}
ObjectFile libruntime_analysis_topdemo.a::topDemoLib.o {
	NAME Object file topDemoLib.o from archive libruntime_analysis_topdemo.a
	EXPORTS cpuLoadTestStart cpuLoadTestStop cacheTestBad cacheTestGood topDemoStop topDemoStart intLockerStart intLockerStop idleTaskStart idleTaskStop taskMoverStart taskMoverStop
	IMPORTS .TOC. cafe_demo_load_test_start cafe_demo_load_test_stop cafe_demo_cache_bad cafe_demo_cache_good cafe_demo_multi_stop cafe_demo_multi_start cafe_demo_intlock_start cafe_demo_intlock_stop cafe_demo_idletask_start cafe_demo_idletask_stop cafe_demo_task_mover_start cafe_demo_task_mover_stop
	DECLARES 
	USES 
}
Module topDemoLib.o {
	OBJECT += libruntime_analysis_topdemo.a::topDemoLib.o
}
ObjectFile libruntime_analysis_topdemo.a::a.o {
	NAME Object file a.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_a
	IMPORTS .TOC. tree_b tree_c tree_x
	DECLARES a_a
	USES 
}
Module a.o {
	OBJECT += libruntime_analysis_topdemo.a::a.o
}
ObjectFile libruntime_analysis_topdemo.a::b.o {
	NAME Object file b.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_b
	IMPORTS .TOC. tree_c tree_d
	DECLARES b_b
	USES 
}
Module b.o {
	OBJECT += libruntime_analysis_topdemo.a::b.o
}
ObjectFile libruntime_analysis_topdemo.a::c.o {
	NAME Object file c.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_c
	IMPORTS .TOC. tree_d
	DECLARES c_c
	USES 
}
Module c.o {
	OBJECT += libruntime_analysis_topdemo.a::c.o
}
ObjectFile libruntime_analysis_topdemo.a::d.o {
	NAME Object file d.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_d
	IMPORTS .TOC.
	DECLARES d_d
	USES 
}
Module d.o {
	OBJECT += libruntime_analysis_topdemo.a::d.o
}
ObjectFile libruntime_analysis_topdemo.a::x.o {
	NAME Object file x.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_x
	IMPORTS .TOC. tree_c tree_y
	DECLARES x_x
	USES 
}
Module x.o {
	OBJECT += libruntime_analysis_topdemo.a::x.o
}
ObjectFile libruntime_analysis_topdemo.a::y.o {
	NAME Object file y.o from archive libruntime_analysis_topdemo.a
	EXPORTS tree_y
	IMPORTS .TOC.
	DECLARES y_y
	USES 
}
Module y.o {
	OBJECT += libruntime_analysis_topdemo.a::y.o
}
Library libruntime_analysis_topdemo.a {
	MODULES libruntime_analysis_topdemo.a::cafe_top_demo.o libruntime_analysis_topdemo.a::topDemoLib.o libruntime_analysis_topdemo.a::a.o libruntime_analysis_topdemo.a::b.o libruntime_analysis_topdemo.a::c.o libruntime_analysis_topdemo.a::d.o libruntime_analysis_topdemo.a::x.o libruntime_analysis_topdemo.a::y.o
}
