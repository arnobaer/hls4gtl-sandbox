<project xmlns="com.autoesl.autopilot.project" name="hls4gtl" top="gtl">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" csimMode="0" lastCsimMode="0" compiler="true"/>
    </Simulation>
    <files xmlns="">
        <file name="../src/gtl_tb_utils.h" sc="0" tb="1" cflags="  -Wno-unknown-pragmas"/>
        <file name="../src/gtl_tb.dat" sc="0" tb="1" cflags="  -Wno-unknown-pragmas"/>
        <file name="../src/gtl_tb.cpp" sc="0" tb="1" cflags=" -std=c++11 -Wno-unknown-pragmas -Wno-unknown-pragmas"/>
        <file name="hls4gtl/src/ap_array.h" sc="0" tb="false" cflags="-std=c++11"/>
        <file name="hls4gtl/src/comb_muon.h" sc="0" tb="false" cflags="-std=c++11"/>
        <file name="hls4gtl/src/gtl.cpp" sc="0" tb="false" cflags="-std=c++11"/>
        <file name="hls4gtl/src/gtl.h" sc="0" tb="false" cflags="-std=c++11"/>
        <file name="hls4gtl/src/types.h" sc="0" tb="false" cflags=""/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

