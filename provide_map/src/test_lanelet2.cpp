#include <ros/ros.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <lanelet2_core/geometry/Lanelet.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_projection/UTM.h>
#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include <lanelet2_routing/LaneletPath.h>
#include <lanelet2_core/geometry/Area.h>
#include <lanelet2_core/geometry/Lanelet.h>

#include <boost/geometry/algorithms/equals.hpp>

#include "lanelet2_core/geometry/LineString.h"
#include "lanelet2_core/geometry/Polygon.h"
#include "lanelet2_core/primitives/CompoundPolygon.h"
#include "lanelet2_core/primitives/Lanelet.h"
#include "lanelet2_core/primitives/RegulatoryElement.h"

using namespace lanelet;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle n;

    // Load a map
    LaneletMapPtr map = load("../catkin_ws/src/provide_map/res/ARC_lanes.osm", Origin({1.3, 103.8})); // origin has to be close to the map data in lat/lon coordinates

    // // Initialize traffic rules
    // TrafficRulesPtr trafficRules{TrafficRulesFactory::instance().create(Locations::Germany, Participants::Vehicle)};

    int laneID;
    std::ofstream outputFile;
    std::stringstream ss;
    
    std::cout << "Enter ID Of lanelet:";
    std::cin >> laneID;

    ConstLanelet lanelet = map->laneletLayer.get(laneID);
    
    ss << laneID;
    std::string fileName = ss.str();
    
    std::string path ="/home/anjun/catkin_ws/src/provide_map/centerline/" + fileName + ".txt";
    
    outputFile.open(path);
    
    for(const ConstPoint3d& point : lanelet.centerline())
    {
        outputFile << point.x() << ", " << point.y() << "\n";
    }

    lanelet.resetCache();

    return 0;
}

    // // Optional: Initalize routing costs
    // double laneChangeCost = 2;
    // RoutingCostPtrs costPtrs{std::make_shared<RoutingCostDistance>(laneChangeCost)};

    // // Optional: Initialize config for routing graph:
    // RoutingGraph::Configuration routingGraphConf;
    // routingGraphConf.emplace(std::make_pair(RoutingGraph::ParticipantHeight, Attribute("2.")));

    // // Create routing graph
    // RoutingGraphPtr graph = RoutingGraph::build(map, trafficRules /*, costPtrs, routingGraphConf*/)

    // std::cout<<lanelet.centerline();


    //ConstLineString3d centerline = lanelet.centerline();
    
    //lanelet.resetCache();


    //Optional<routing::LaneletPath> shortestPath = graph->shortestPath(fromLanelet, toLanelet);

    // Optional<Route> route = graph->getRoute(fromLanelet, toLanelet, routingCostId);
    // if (route) {
    //     LaneletSubmapConstPtr routeMap = route->laneletSubmap();
    //     write("route.osm", *routeMap->laneletMap(), Origin({49, 8}));
    // }
//     return 0;

// }

