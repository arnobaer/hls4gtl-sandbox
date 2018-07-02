<project xmlns="com.autoesl.autopilot.project" name="hls4gtl" top="gtl">
    <files>
        <file name="hls4gtl/include/hls4gtl/comb_muon.h" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="hls4gtl/include/hls4gtl/gtl.h" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="hls4gtl/include/hls4gtl/types.h" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="hls4gtl/src/gtl.cpp" sc="0" tb="false" cflags="-Ihls4gtl/include"/>
        <file name="../test/gtl_tb.cpp" sc="0" tb="true" cflags="-I../../../include"/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" csimMode="0" lastCsimMode="0" compiler="true"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>
