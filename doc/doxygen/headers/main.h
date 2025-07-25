// ------------------------------------------------------------------------
//
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2006 - 2024 by the deal.II authors
//
// This file is part of the deal.II library.
//
// Part of the source code is dual licensed under Apache-2.0 WITH
// LLVM-exception OR LGPL-2.1-or-later. Detailed license information
// governing the source code and code contributions can be found in
// LICENSE.md and CONTRIBUTING.md at the top level directory of deal.II.
//
// ------------------------------------------------------------------------


/**
 * @mainpage
 *
 * This is the main starting page for the deal.II class and function
 * documentation. Documentation on other aspects, such as the build
 * system, can be found elsewhere. In addition, there are
 * <a href="Tutorial.html">Tutorial programs on the use of the library</a>.
 *
 * Many of the classes in the deal.II library can be grouped into topics (see
 * the "Topics" tab at the top of this page). These topics form around the building
 * blocks of any finite element program. An outline of how the primary groups
 * of classes in deal.II interact is given by the following clickable graph,
 * with a more detailed description below (gray boxes denote a subset of the
 * optional external libraries, gray ovals a subset of the optional external
 * applications with which deal.II can interact):
 *
 * @dot
 digraph G
{
  graph[rankdir="TB",bgcolor="transparent"];

  node [fontname="FreeSans",fontsize=15,
        shape=record,height=0.2,width=0.4,
        color="cornflowerblue", fillcolor="white", style="filled"];
  edge [color="cornflowerblue", weight=10];

  tria       [label="Triangulation",    URL="\ref grid"];
  fe         [label="Finite elements",    URL="\ref feall"];
  mapping    [label="Mapping",          URL="\ref mapping"];
  quadrature [label="Quadrature",       URL="\ref Quadrature"];
  dh         [label="DoFHandler",       URL="\ref dofs"];
  fevalues   [label="FEValues",         URL="\ref feaccess"];
  systems    [label="Linear systems",   URL="\ref LAC"];
  solvers    [label="Linear solvers",   URL="\ref Solvers"];
  output     [label="Graphical output", URL="\ref output"];
  manifold   [label="Manifold",         URL="\ref manifold"];


  tria -> dh              [style="solid"];
  fe -> dh                [style="solid"];
  fe -> fevalues          [style="solid"];
  mapping -> fevalues     [style="solid"];
  quadrature -> fevalues  [style="solid"];
  dh -> systems           [style="solid"];
  fevalues -> systems     [style="solid"];
  systems -> solvers      [style="solid"];
  solvers -> output       [style="solid"];
  manifold -> tria        [style="solid"];
  manifold -> mapping     [style="solid"];

  node [fontname="FreeSans",fontsize=12,
        shape=record,height=0.2,width=0.4,
        color="gray55", fontcolor="gray55", fillcolor="white", style="filled"];
  edge [color="gray55", weight=1];

  opencascade [label="OpenCASCADE", URL="\ref OpenCASCADE"];

  subgraph linalglibs {
    rank="same";
    petsc       [label="PETSc",    URL="\ref PETScWrappers"];
    trilinos    [label="Trilinos", URL="\ref TrilinosWrappers"];
  }
  umfpack     [label="UMFPACK"];

  petsc -> systems        [dir="none"];
  petsc -> solvers        [dir="none"];
  trilinos -> systems     [dir="none"];
  trilinos -> solvers     [dir="none"];
  umfpack -> solvers      [dir="none"];
  opencascade -> manifold [dir="none"];


  node [fontname="FreeSans",fontsize=12,
        shape=ellipse,height=0.2,width=0.4,
        color="gray55", fontcolor="gray55", fillcolor="white", style="filled"];
  edge [color="gray55", weight=1];

  kokkos      [label="Kokkos"];
  gmsh        [label="gmsh", URL="\ref Gmsh"];
  visit       [label="VisIt"]
  paraview    [label="ParaView"]

  kokkos -> systems  [dir="none"];
  gmsh -> tria       [dir="none"];
  output -> visit    [dir="none"];
  output -> paraview [dir="none"];
}
 * @enddot
 *
 * These groups are all covered in the tutorial programs, with a first
 * overview of how they fit together given in step-3. The following
 * is a guide to this classification of groups, as well as links
 * to the documentation pertaining to each of them:
 *
 * <ol>
 *   <li> <b>%Triangulation</b>: Triangulations are collections of
 *   cells and their lower-dimensional boundary objects. Cells are
 *   images of the reference hypercube [0,1]<sup>dim</sup> under a
 *   suitable mapping in the topic on @ref mapping.
 *
 *   The triangulation stores geometric and topological
 *   properties of a mesh: how are the cells connected and where are
 *   their vertices. A triangulation doesn't know
 *   anything about the finite elements that you may want to used on
 *   this mesh, and a triangulation does not even know anything about
 *   the shape of its cells: in 2d it only knows that a cell has 4
 *   faces (lines) and 4 vertices (and in 3d that it has 6 faces
 *   (quadrilaterals), 12 lines, and 8 vertices), but everything else
 *   is defined by a mapping class.
 *
 *   The properties and data of triangulations are almost always
 *   queried through loops over all cells, possibly querying all faces
 *   of each cell as well. Most
 *   of the knowledge about a mesh is therefore hidden behind
 *   @em iterators, i.e. pointer-like structures that one can
 *   iterate from one cell to the next, and that one can ask for
 *   information about the cell it presently points to.
 *
 *   The classes that describe triangulations and cells are located
 *   and documented in the @ref grid topic. Iterators are described
 *   in the @ref Iterators topic.
 *
 *   <li> <b>%Manifold</b>: Manifolds describe the shape of cells and,
 *   more generally, the geometry of the domain on which one wants
 *   to solve an equation. They use the language of differential
 *   geometry. More information can be found in @ref manifold.
 *
 *   <li> <b>Finite Element</b>: Finite element classes describe the
 *   properties of a finite element space as defined on the unit
 *   cell. This includes, for example, how many degrees of freedom are
 *   located at vertices, on lines, or in the interior of cells. In
 *   addition to this, finite element classes of course have to
 *   provide values and gradients of individual shape functions at
 *   points on the unit cell.
 *
 *   The finite element classes are described in the @ref feall topic.
 *
 *   <li> <b>%Quadrature</b>: As with finite elements, quadrature
 *   objects are defined on the unit cell. They only describe the
 *   location of quadrature points on the unit cell, and the weights
 *   of quadrature points thereon.
 *
 *   The documentation of the classes describing particular quadrature
 *   formulas is found in the @ref Quadrature topic.
 *
 *   <li> <b>%DoFHandler</b>: %DoFHandler objects are the confluence
 *   of triangulations and finite elements: the finite element class
 *   describes how many degrees of freedom it needs per vertex, line,
 *   or cell, and the DoFHandler class allocates this space so that
 *   each vertex, line, or cell of the triangulation has the correct
 *   number of them. It also gives them a global numbering.
 *
 *   A different viewpoint is this: While the mesh and finite element describe
 *   abstract properties of the finite dimensional space $V_h$ in which we
 *   seek the discrete solution, the %DoFHandler classes enumerate a concrete
 *   basis of this space so that we can represent the discrete solution as
 *   $u_h(\mathbf x)= \sum_j U_j \varphi_i(\mathbf x)$ by an ordered set of
 *   coefficients $U_j$.
 *
 *   Just as with triangulation objects, most operations on
 *   DoFHandlers are done by looping over all cells and doing something
 *   on each or a subset of them. The interfaces of the two classes are
 *   therefore rather similar: they allow to get iterators to the
 *   first and last cell (or face, or line, etc) and offer information
 *   through these iterators. The information that can be gotten from
 *   these iterators is the geometric and topological information that
 *   can already be gotten from the triangulation iterators (they are
 *   in fact derived classes) as well as things like the global
 *   numbers of the degrees of freedom on the present cell. On can
 *   also ask an iterator to extract the values corresponding to the
 *   degrees of freedom on the present cell from a data vector that
 *   stores values for all degrees of freedom associated with a
 *   triangulation.
 *
 *   It is worth noting that, just as triangulations, DoFHandler
 *   classes do not know anything about the mapping from the unit cell
 *   to its individual cells. It is also ignorant of the shape
 *   functions that correspond to the degrees of freedom it manages:
 *   all it knows is that there are, for example, 2 degrees of freedom
 *   for each vertex and 4 per cell interior. Nothing about their
 *   specifics is relevant to the DoFHandler class with the exception of
 *   the fact that they exist.
 *
 *   The DoFHandler class and its associates are described in the
 *   @ref dofs topic. In addition, there are specialized versions that can
 *   handle multilevel and hp-discretizations. These are described in
 *   the @ref mg and @ref hp topics. Finite element methods frequently
 *   imply constraints on degrees of freedom, such as for hanging nodes
 *   or nodes at which boundary conditions apply; dealing with such
 *   constraints is described in the @ref constraints topic.
 *
 *   <li> <b>%Mapping</b>: The next step in a finite element program
 *   is that one would want to compute matrix and right hand side
 *   entries or other quantities on each cell of a triangulation,
 *   using the shape functions of a finite element and quadrature
 *   points defined by a quadrature rule. To this end, it is necessary
 *   to map the shape functions, quadrature points, and quadrature
 *   weights from the unit cell to each cell of a triangulation. This
 *   is not directly done by, but facilitated by the Mapping and
 *   derived classes: they describe how to map points from unit to
 *   real space and back, as well as provide gradients of this
 *   derivative and Jacobian determinants.
 *
 *   These classes are all described in the @ref mapping topic.
 *
 *   <li> <b>%FEValues</b>: The next step is to actually take a finite
 *   element and evaluate its shape functions and their gradients at
 *   the points defined by a quadrature formula when mapped to the
 *   real cell. This is the realm of the FEValues class and siblings:
 *   in a sense, they offer a point-wise view of the finite element
 *   function space.
 *
 *   This seems restrictive: in mathematical analysis, we always write
 *   our formulas in terms of integrals over cells, or faces of cells,
 *   involving the finite element shape functions. One would therefore
 *   think that it is necessary to describe finite element spaces as
 *   continuous spaces. However, in practice, this is not necessary:
 *   all integrals are in actual computations replaced by
 *   approximations using quadrature formula, and what is therefore
 *   really only necessary is the ability to evaluate shape functions
 *   at a finite number of given locations inside a domain. The
 *   FEValues classes offer exactly this information: Given finite
 *   element, quadrature, and mapping objects, they compute the
 *   restriction of a continuous function space (as opposed to
 *   discrete, not as opposed to discontinuous) to a discrete number
 *   of points.
 *
 *   There are a number of objects that can do this: FEValues for
 *   evaluation on cells, FEFaceValues for evaluation on faces of
 *   cells, and FESubfaceValues for evaluation on parts of faces of
 *   cells. All these classes are described in the @ref feaccess
 *   topic.
 *
 *   <li> <b>Linear Systems</b>: If one knows how to evaluate the
 *   values and gradients of shape functions on individual cells using
 *   FEValues and friends, and knows how to get the global numbers of
 *   the degrees of freedom on a cell using the DoFHandler iterators,
 *   then the next step is to use the bilinear form of the problem to
 *   assemble the system matrix (and right hand side) of the linear
 *   system. We will then determine the solution of our problem from
 *   this linear system.
 *
 *   To do this, we need to have classes that store and manage the
 *   entries of matrices and vectors. deal.II comes with a whole set
 *   of classes for this purpose, as well as with interfaces to other
 *   software packages that offer similar functionality. Documentation
 *   to this end can be found in the @ref LAC topic.
 *
 *   <li> <b>Linear Solvers</b>: In order to determine the solution of
 *   a finite-dimensional, linear system of equations, one needs
 *   linear solvers. In finite element applications, they are
 *   frequently iterative, but sometimes one may also want to use
 *   direct or sparse direct solvers. deal.II has quite a number of
 *   these. They are documented in the @ref Solvers topic.
 *
 *   <li> <b>Output</b>: Finally, once one has obtained a solution of
 *   a finite element problem on a given triangulation, one will often
 *   want to postprocess it using a visualization program. This
 *   library doesn't do the visualization by itself, but rather generates output
 *   files in a variety of graphics formats understood by widely
 *   available visualization tools.
 *
 *   A description of the classes that do so is given in the
 *   @ref output topic.
 * </ol>
 *
 * In addition, deal.II has a number of groups of classes that go
 * beyond the ones listed here. They pertain to more refined concepts
 * of the hierarchy presented above, or to tangential aspects like
 * handling of input and output that are not necessarily specific to
 * finite element programs, but appear there as well. These classes
 * are all listed in the Classes and Namespaces views reachable from
 * the menu bar at the top of this page, and are also grouped into
 * topics of their own (see the "Topics" tab at the top of this page).
 *
 * We provide the Doxygen tag file for those of you who would like to directly link the
 * documentation of application programs to the deal.II online documentation. The tag file
 * is at <a href="../deal.tag"><code>deal.tag</code></a>. For each release of deal.II,
 * it resides in the directory right above the Doxygen reference documentation. In order
 * to use the tag file, you have to download it into a place where Doxygen can find it.
 * After that, find the key <code>TAGFILES</code> in your Doxygen options file and write something like
 * <pre>
 * TAGFILES = deal.tag=https://www.dealii.org/X.Y.Z/doxygen/deal.II
 * </pre>
 * where <code>X.Y.Z</code> refers to the release you want to link to. Be sure you use
 * the matching tag file. In theory, you can also link against the developing revisions
 * of deal.II, but then you have to fear that your links may become invalid if
 * the deal.II structure changes.
 */
