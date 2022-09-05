#include "geo.h"
#include "libs.h"
#include "paths.h"
#include "qry.h"
#include "srb_tree.h"
#include "svg.h"
#include "system.h"

void main(int argc, char** argv) {
    Controller my_ctrl = createController();
    Paths my_paths = createAllPaths();
    SRBTree my_tree = createSRB(0);

    readParam(argc, argv, my_paths, my_ctrl);

    if (checkBED(my_ctrl) && checkGEO(my_ctrl) && checkBSD(my_ctrl)) {
        readGeo(getBedGeo(my_paths), my_tree);
        writeSvg(createSvg(getBsdGeoSvg(my_paths)), my_tree);
        printSRB(my_tree, getBsdGeoDot(my_paths);

    } else {
        return 0;  // ERRO!
    }

    if (checkQRY(my_ctrl)) {
        readQry(my_tree, getBedQry(my_paths), getBsdGeoQrySvg(my_paths), getBsdGeoQryTxt(my_paths));
        printSRB(my_tree, getBsdGeoQryDot(my_paths);
    }
    killSRB(my_tree);
    freePaths(my_paths);
    freeCtrl(my_ctrl);
}
