#!/usr/bin/env python
import lanelet2
import tempfile
import os

osm_path = os.path.join(os.path.dirname(os.path.abspath('')),"provide_map/res/mapping_example.osm")
print("using OSM: %s (exist? %s)" %(osm_path, os.path.exists(osm_path)))

pr = lanelet2.projection.UtmProjector(lanelet2.io.Origin(49,8))
lmap, err_list = lanelet2.io.loadRobust(osm_path, pr)

print("%d errors, %d lanes detected" % (len(err_list), len({l for l in lmap.laneletLayer})))

trafficRules = lanelet2.traffic_rules.create(lanelet2.traffic_rules.Locations.Germany, lanelet2.traffic_rules.Participants.Vehicle)
graph = lanelet2.routing.RoutingGraph(lmap, trafficRules)

startLane = lmap.laneletLayer[45258]
endLane = lmap.laneletLayer[45260]

rt = graph.getRoute(startLane, endLane)
lpath = rt.shortestPath()

print ("found a path of %d lanes" % len(lpath))#rt.numLanes())

for ll in graph.shortestPath(startLane, endLane):
    print(ll)                 

routingCostId = 0

route = graph.getRoute(startLane, endLane, routingCostId)
if route:
    laneletSubmap = route.laneletSubmap()
    lanelet2.io.write("route.osm", laneletSubmap.laneletMap(), lanelet2.io.Origin(49, 8))
