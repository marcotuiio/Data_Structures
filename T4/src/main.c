#include "digraph.h"
#include "geo.h"
#include "libs.h"
#include "paths.h"
#include "rb_tree.h"
#include "via.h"
// #include "qry.h"
#include "svg.h"
#include "system.h"

int main(int argc, char* argv[]) {
    Controller my_ctrl = createController();
    Paths my_paths = createAllPaths();
    Digraph my_graph = NULL;
    Rb my_Rb = createRB(0);
    readParam(argc, argv, my_paths, my_ctrl);

    if (checkBED(my_ctrl) && checkGEO(my_ctrl) && checkBSD(my_ctrl)) {
        puts(getBsdGeoSvg(my_paths));
        readGeo(getBedGeo(my_paths), my_Rb);
        my_graph = readVia(getBedVia(my_paths));
        writeSvg(createSvg(getBsdGeoSvg(my_paths)), my_Rb, my_graph);

    } else {
        printf("ERROR: INPUT FILES OR OUTPUT DIRECTORIES HAVE NOT BEEN READ\n");
        return -1;  // ERRO!
    }

    // if (checkQRY(my_ctrl)) {
    //     readQry(my_graph, getBedQry(my_paths), getBsdGeoQrySvg(my_paths), getBsdGeoQryTxt(my_paths));
    // }

    killRB(my_Rb);
    killGraph(my_graph);
    freePaths(my_paths);
    freeCtrl(my_ctrl);

    return 0;
}
