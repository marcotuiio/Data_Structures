#include "libs.h"
#include "paths.h"
#include "system.h"
#include "tree.h"
#include "geo.h"
#include "svg.h"

int main(int argc, char** argv) {
    Paths my_paths = createAllPaths();
    Tree my_tree = createTree();

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
    printf("\ntree %p\n", getRoot(my_tree));
    printTree(my_tree);

    writeSvg(getBsdGeoSvg(my_paths), my_tree);
    printf("4\n");

    freePaths(my_paths);

    return 0;
}