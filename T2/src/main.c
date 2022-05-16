#include "libs.h"
#include "paths.h"
#include "system.h"
#include "tree.h"
#include "geo.h"

int main(int argc, char** argv) {
    Paths my_paths = createAllPaths();
    //Tree my_tree = createTree(NULL, 0, 0);

    readParam(argc, argv, my_paths);

    puts(getBed(my_paths));
    puts(getBsd(my_paths));

    puts(getBedGeo(my_paths));
    puts(getGeoArq(my_paths));
    puts(getGeoName(my_paths));

    puts(getBedQry(my_paths));
    puts(getQryArq(my_paths));
    puts(getQryName(my_paths));

    puts(getBsdGeoSvg(my_paths));
    puts(getBsdGeoQrySvg(my_paths));
    puts(getBsdGeoQryTxt(my_paths));

    readGeo(getBedGeo(my_paths), my_tree);

    freePaths(my_paths);
    freeTree(my_tree);

    return 0;
}