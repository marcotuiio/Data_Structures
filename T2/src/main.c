#include "geo.h"
#include "libs.h"
#include "paths.h"
#include "svg.h"
#include "system.h"
#include "tree.h"

int main(int argc, char** argv) {
    Controller my_ctrl = createController();
    Paths my_paths = createAllPaths();
    Tree my_tree = createTree();

    readParam(argc, argv, my_paths, my_ctrl);

    // printf("\n");
    // puts(getBed(my_paths));
    // puts(getBsd(my_paths));

    // puts(getBedGeo(my_paths));
    // puts(getGeoArq(my_paths));
    // puts(getGeoName(my_paths));

    // puts(getBedQry(my_paths));
    // puts(getQryArq(my_paths));
    // puts(getQryName(my_paths));

    // puts(getBsdGeoSvg(my_paths));
    // puts(getBsdGeoQrySvg(my_paths));
    // puts(getBsdGeoQryTxt(my_paths));
    // printf("\n");

    if (checkBED(my_ctrl) && checkGEO(my_ctrl) && checkBSD(my_ctrl)) {
        readGeo(getBedGeo(my_paths), my_tree);

        writeSvg(getBsdGeoSvg(my_paths), my_tree);
    } else {
        return 0;  // ERRO!
    }

    // if (checkQRY(my_ctrl)) {
    //     //executar qry
    // }

    freeTree(getRoot(my_tree));
    free(my_tree);
    freePaths(my_paths);
    freeCtrl(my_ctrl);

    return 0;
}