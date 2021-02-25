import lanelet2
pr = lanelet2.projection.UtmProjector(lanelet2.io.Origin(49,8.4))
map = lanelet2.io.load("res/mapping_example.osm", pr)
trafficRules = lanelet2.traffic_rules.create(lanelet2.traffic_rules.Locations.Germany, lanelet2.traffic_rules.Participants.Vehicle)
graph = lanelet2.routing.RoutingGraph(map, trafficRules)
ll1 = map.laneletLayer[45258]
ll2 = map.laneletLayer[45260]
for ll in graph.shortestPath(ll1, ll2):
    print(ll)
