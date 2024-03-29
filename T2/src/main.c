#include "geo.h"
#include "libs.h"
#include "paths.h"
#include "qry.h"
#include "svg.h"
#include "system.h"

int main(int argc, char** argv) {
    Controller my_ctrl = createController();
    Paths my_paths = createAllPaths();
    Tree my_tree = createTree();

    readParam(argc, argv, my_paths, my_ctrl);

    if (checkBED(my_ctrl) && checkGEO(my_ctrl) && checkBSD(my_ctrl)) {
        readGeo(getBedGeo(my_paths), my_tree);

        writeSvg(getBsdGeoSvg(my_paths), my_tree);

    } else {
        return 0;  // ERRO!
    }

    if (checkQRY(my_ctrl)) {
        readQry(my_tree, getBedQry(my_paths), getBsdGeoQrySvg(my_paths), getBsdGeoQryTxt(my_paths));
    }

    freeTree(getRoot(my_tree));
    free(my_tree);
    freePaths(my_paths);
    freeCtrl(my_ctrl);

    return 0;
}