#include "digraph.h"
#include "geo.h"
#include "libs.h"
#include "paths.h"
// #include "qry.h"
// #include "svg.h"
#include "system.h"

int main(int argc, char* argv[]) {
    Controller my_ctrl = createController();
    Paths my_paths = createAllPaths();
    Digraph my_graph = createGraph(200);
    readParam(argc, argv, my_paths, my_ctrl);

    // if (checkBED(my_ctrl) && checkGEO(my_ctrl) && checkBSD(my_ctrl)) {
    //     readGeo(getBedGeo(my_paths), my_graph);
    //     writeSvg(createSvg(getBsdGeoSvg(my_paths)), my_graph);
    //     printSRB(my_graph, getBsdGeoDot(my_paths));
                 
    // } else {
    //     printf("ERROR: INPUT FILES OR OUTPUT DIRECTORIES HAVE NOT BEEN READ\n");
    //     return -1;  // ERRO!
    // }
    
    // if (checkQRY(my_ctrl)) {
    //     readQry(my_graph, getBedQry(my_paths), getBsdGeoQrySvg(my_paths), getBsdGeoQryTxt(my_paths));
    //     printSRB(my_graph, getBsdGeoQryDot(my_paths));
    // }
                 
    killGraph(my_graph);
    freePaths(my_paths);
    freeCtrl(my_ctrl);

    return 0;
}
