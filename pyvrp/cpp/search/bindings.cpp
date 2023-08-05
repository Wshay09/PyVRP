#include "Exchange.h"
#include "LocalSearch.h"
#include "MoveTwoClientsReversed.h"
#include "RelocateStar.h"
#include "Route.h"
#include "SwapStar.h"
#include "TwoOpt.h"
#include "search_docs.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>

namespace py = pybind11;

using pyvrp::search::Exchange;
using pyvrp::search::LocalSearch;
using pyvrp::search::LocalSearchOperator;
using pyvrp::search::MoveTwoClientsReversed;
using pyvrp::search::RelocateStar;
using pyvrp::search::Route;
using pyvrp::search::SwapStar;
using pyvrp::search::TwoOpt;

PYBIND11_MODULE(_search, m)
{
    using NodeOp = LocalSearchOperator<pyvrp::search::Route::Node>;
    using RouteOp = LocalSearchOperator<pyvrp::search::Route>;

    py::class_<NodeOp>(m, "NodeOperator");
    py::class_<RouteOp>(m, "RouteOperator");

    py::class_<Exchange<1, 0>, NodeOp>(
        m, "Exchange10", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<2, 0>, NodeOp>(
        m, "Exchange20", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<3, 0>, NodeOp>(
        m, "Exchange30", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<1, 1>, NodeOp>(
        m, "Exchange11", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<2, 1>, NodeOp>(
        m, "Exchange21", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<3, 1>, NodeOp>(
        m, "Exchange31", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<2, 2>, NodeOp>(
        m, "Exchange22", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<3, 2>, NodeOp>(
        m, "Exchange32", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Exchange<3, 3>, NodeOp>(
        m, "Exchange33", DOC(pyvrp, search, Exchange))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<LocalSearch>(m, "LocalSearch")
        .def(py::init<pyvrp::ProblemData const &,
                      std::vector<std::vector<size_t>>>(),
             py::arg("data"),
             py::arg("neighbours"),
             py::keep_alive<1, 2>())  // keep data alive until LS is freed
        .def("add_node_operator",
             &LocalSearch::addNodeOperator,
             py::arg("op"),
             py::keep_alive<1, 2>())
        .def("add_route_operator",
             &LocalSearch::addRouteOperator,
             py::arg("op"),
             py::keep_alive<1, 2>())
        .def("set_neighbours",
             &LocalSearch::setNeighbours,
             py::arg("neighbours"))
        .def("get_neighbours",
             &LocalSearch::getNeighbours,
             py::return_value_policy::reference_internal)
        .def("__call__",
             &LocalSearch::operator(),
             py::arg("solution"),
             py::arg("cost_evaluator"))
        .def("search",
             py::overload_cast<pyvrp::Solution const &,
                               pyvrp::CostEvaluator const &>(
                 &LocalSearch::search),
             py::arg("solution"),
             py::arg("cost_evaluator"))
        .def("intensify",
             py::overload_cast<pyvrp::Solution const &,
                               pyvrp::CostEvaluator const &,
                               double const>(&LocalSearch::intensify),
             py::arg("solution"),
             py::arg("cost_evaluator"),
             py::arg("overlap_tolerance") = 0.05)
        .def("shuffle", &LocalSearch::shuffle, py::arg("rng"));

    py::class_<MoveTwoClientsReversed, NodeOp>(m, "MoveTwoClientsReversed")
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<RelocateStar, RouteOp>(m, "RelocateStar")
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<SwapStar, RouteOp>(m, "SwapStar", DOC(pyvrp, search, SwapStar))
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<TwoOpt, NodeOp>(m, "TwoOpt")
        .def(py::init<pyvrp::ProblemData const &>(),
             py::arg("data"),
             py::keep_alive<1, 2>());  // keep data alive

    py::class_<Route>(m, "Route", DOC(pyvrp, search, Route))
        .def(py::init<pyvrp::ProblemData const &, size_t, size_t>(),
             py::arg("data"),
             py::arg("idx"),
             py::arg("vehicle_type"),
             py::keep_alive<1, 2>())  // keep data alive
        .def_property_readonly("idx", &Route::idx)
        .def_property_readonly("vehicle_type", &Route::vehicleType)
        .def("__delitem__", &Route::remove, py::arg("idx"))
        .def("__getitem__",
             &Route::operator[],
             py::arg("idx"),
             py::return_value_policy::reference_internal)
        .def(
            "__iter__",
            [](Route const &route) {
                return py::make_iterator(route.begin(), route.end());
            },
            py::return_value_policy::reference_internal)
        .def("__len__", &Route::size)
        .def("__str__",
             [](Route const &route) {
                 std::stringstream stream;
                 stream << route;
                 return stream.str();
             })
        .def("is_feasible", &Route::isFeasible)
        .def("has_excess_load", &Route::hasExcessLoad)
        .def("has_time_warp", &Route::hasTimeWarp)
        .def("capacity",
             [](Route const &route) { return route.capacity().get(); })
        .def("load", [](Route const &route) { return route.load().get(); })
        .def("time_warp", &Route::timeWarp)
        .def(
            "dist_between",
            [](Route const &route, size_t start, size_t end) {
                return route.distBetween(start, end).get();
            },
            py::arg("start"),
            py::arg("end"))
        .def(
            "load_between",
            [](Route const &route, size_t start, size_t end) {
                return route.loadBetween(start, end).get();
            },
            py::arg("start"),
            py::arg("end"))
        .def("tw_between", &Route::twBetween, py::arg("start"), py::arg("end"))
        .def("overlaps_with",
             &Route::overlapsWith,
             py::arg("other"),
             py::arg("tolerance"))
        .def("append",
             &Route::push_back,
             py::arg("node"),
             py::keep_alive<1, 2>())  // keep node alive
        .def("clear", &Route::clear)
        .def("insert",
             &Route::insert,
             py::arg("idx"),
             py::arg("node"),
             py::keep_alive<1, 3>())  // keep node alive
        .def("update", &Route::update);

    py::class_<Route::Node>(m, "Node", DOC(pyvrp, search, Route, Node))
        .def(py::init<size_t>(), py::arg("loc"))
        .def_property_readonly("client", &Route::Node::client)
        .def_property_readonly("idx", &Route::Node::idx)
        .def_property_readonly("route", &Route::Node::route)
        .def("is_depot", &Route::Node::isDepot);
}
