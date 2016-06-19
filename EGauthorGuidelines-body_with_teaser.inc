% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[Unfolding and Interactive Exploration of Protein Tunnels and their Dynamics]%
      {Unfolding and Interactive Exploration of Protein Tunnels and their Dynamics}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
\author[Koles\'{a}r et al.]
       {TODO$^{1}$ and TODO$^{2}$
%        S. Spencer$^2$\thanks{Chairman Siggraph Publications Board}
        \\
% For Computer Graphics Forum: Please use the abbreviation of your first name.
         $^1$University of Bergen, Norway\\
         $^2$Masaryk University, Brno, Czech Republic
%        $^2$ Another Department to illustrate the use in papers from authors
%             with different affiliations
       }

% ------------------------------------------------------------------------

% if the Editors-in-Chief have given you the data, you may uncomment
% the following five lines and insert it here
%
% \volume{27}   % the volume in which the issue will be published;
% \issue{1}     % the issue number of the publication
% \pStartPage{1}      % set starting page


%-------------------------------------------------------------------------
% Packages
\usepackage[textsize=small,colorinlistoftodos]{todonotes}
% Defines usefull commands.
\newcommand{\ie}{i.e.,~}
\newcommand{\eg}{e.g.,~}


\begin{document}

\teaser{
 \includegraphics[width=\linewidth]{img/teaser.png}
 \centering
  \caption{Our proposed approach enabling to explore an ensemble of protein tunnels. It consists of three main parts -- scatterplot and bar chart representation of different tunnel properties on the bottom and the unfolded view of selected tunnels on the top. }
\label{fig:teaser}
}

\maketitle

\begin{abstract}
The presence of tunnels in protein structures substantially influences their reactivity with other molecules.
Therefore, studying their properties and changes over time has been in the scope of biochemists for decades.
In this paper we introduce a novel approach for comparative visualization and exploration of ensembles of tunnels.
Our goal is to overcome occlusion problems present in traditional tunnel representations while providing users a quick way to navigate  through the input dataset to identify potentially interesting tunnels.
First, we unfold the input tunnels to a 2D representation enabling to observe the mutual position of amino acids forming the tunnel surface and the amount of surface they influence.
These 2D images are subsequently described by image moments commonly used in image processing.
This way we are able to detect similarities and outliers in the dataset, which are visualized as clusters in a scatterplot graph.
The same coloring scheme is used in the linked bar chart enabling to detect the position of the cluster members over time.
These views provide a way to select a subset of potentially interesting tunnels that can be further explored in detail using the 2D unfolded view and also traditional 3D representation.
The usability of our approach is demonstrated on case studies conducted by the domain experts.

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}





%-------------------------------------------------------------------------
\section{Introduction}
Studying molecular structures and their reactivity plays a crucial role in many research disciplines, including drug design, agriculture, cosmetics, industry, and others.
The product of such a reaction can form a basis of new chemical matters, including medication.
The reactivity of a molecule is highly influenced by the presence of a void space inside its structure. 
More densely packed molecules, i.e., those not having too much empty space between atoms, are hardly accessible by small ligands aiming to react deeply inside the molecule. 
Therefore, by exploring the amount and properties of void space inside molecules we are able to assess the possibility of a ligand with specific properties to enter these molecules.
The void space can be categorized according to different criteria, the most common approach takes into account the accessibility of the void space form the molecular surface.
Then we can distinguish between inner closed cavities and paths.
The closed cavities are inaccessible from the surface and are buried in the molecular structure.
The accessible paths can be further divided to those which connect a specific site (so called active site) inside the molecule with its surface and those traversing the whole molecule.
The first type of paths is denoted as tunnels and the second as channels or pores.
In our research we are interested mainly in tunnels in protein molecules because they enable to transport small ligands to the protein active site where a mutual chemical reaction can occur.  
This process is crucial namely in drug design and protein engineering.
From the latter field also comes our conducted user study which we present at the end of the paper.
In our research we are focusing namely on protein structures, however, the proposed method is applicable to any kind of molecule containing tunnels.

Molecules are not static structures, their atoms are in permanent movement.
This has also the impact on the void space, when detected tunnels can become wider or narrower or can even disappear. 
Recently it was revealed that the function of proteins is determined not only by their constitution but also their molecular dynamics~\cite{dynasome}. 
Therefore, from the biochemical point of view studying protein tunnels in one static time step is not too relevant because a given tunnel can be opened only for a fraction of time.
Biochemists are rather interested in the stability and changes of tunnel shape over time.
This exploration process has to be supported by special visualization techniques.

The majority of existing tunnel representations aim to visualize the 3D surface depicting the tunnel shape. 
However, such representations fail in cases when it is required to compare more tunnels at once.
This can happen namely in situations when we want to explore:
\begin{itemize}
\item changes of a tunnel in molecular dynamics
\item several mutations of amino acids around a given tunnel
\end{itemize}

When performing these tasks using traditional 3D visualization, the first situation uses the animation of tunnel movement and the second situation superposes the tunnel under different mutations.
Both cases suffer from several drawbacks. 
When dealing with large molecular dynamics simulations consisting of hundreds of thousands of time steps, the animation of this movement is very hard to explore.
The user is overwhelmed by movements and the differences in the tunnel shape can be easily overlooked.
Moreover, using the 3D tunnel representation only a portion of the tunnel surface is visible from the viewpoint.
When aiming to explore a tunnel influenced by several mutations of its surrounding amino acids, the user wants to observe and evaluate the impact of these mutations on the tunnel surface. Using superposition of the mutated tunnels we suffer from visual clutter caused by surface overlaps (see Figure~\ref{fig:tunnels} left).
These overlaps can be removed by using juxtaposition of the tunnel representations (see Figure~\ref{fig:tunnels} right).
But such a case is applicable only on a small set of objects because it can be hard to perceive the differences between them, namely for those having a further mutual distance. 
This problem is even stressed when using the 3D tunnel representation.

\begin{figure}[htb]
 \includegraphics[width=\linewidth]{img/tunnels.png}
 \centering
  \caption{Left: superposed representation of five conformations of a tunnel differing by one mutated amino acid. Right: juxtaposed view of these conformations.}
\label{fig:tunnels}
\end{figure}

Moreover, the proper visualization of surface itself is not sufficient for exploration and complete understanding of differences between protein tunnels. 
Another essential information relates the amino acids forming the tunnel boundary, namely their biochemical properties and the extent of influence of the tunnel.
Possible solution is to map this information onto the tunnel surface.
Nevertheless, due to the aforementioned problems present in 3D tunnel visualization mentioned above, it is hard to compare and explore these properties as well.

In this paper we aim at solving these problems by introducing a novel technique for intuitive comparison and exploration of ensembles of protein tunnels.
It consists of several linked views enabling to:
\begin{itemize}
\item get the overview of all tunnels in the input ensemble and spot possibly interesting tunnels 
\item localize these tunnels in time
\item visualize selected tunnels using 2D unfolded view and compare their amino acid constitution and influence
\item combine the unfolded view with the traditional 3D view to see the original shape 
\end{itemize}

The benefit of our approach is demonstrated on two case studies conducted by the biochemists.


\section{Related Work}
The problem of visual exploration of spatial structures of tubular shape has been already partially addressed in other domains as well, e.g., in medical visualization.
Here the methods based on 3D data projections and reformations are frequently used in order to reveal various anatomical features.
Nevertheless, due to the nature of the data, these methods mostly focus on the exploration rather than comparison.
On the other hand, the comparative visualization in connection with surface reformation was applied many times when studding the flow dynamics.

In the following sections we touch upon related existing approaches in more detail. 
First we provide the reader with an overview of the related work regarding the protein void detection and their visualization. 
Then we mention techniques which have been proposed for 3D data projections and reformation in medical visualization, flow dynamics, and other fields.

\subsection{Protein Void Detection and Analysis}
The earliest approaches for protein tunnel detection were based on grids~\cite{Petrek2006Caver, Ho2008Hollow, Voss20103V}. 
For instance, Petrek et al.~\cite{Petrek2006Caver} proposed to enclose the protein into a uniform grid.
The value of each grid cell corresponds to the distance of this cell to the nearest atom.
Then the Dijkstra algorithm is used in order to find the set of tunnels consisting of cells with the largest distance to the surrounding atoms.

Even though these techniques allow to describe the void space of nearly any shape, the precision and performance of the grid-based methods highly depends on the grid resolution. 
These drawbacks were later overcome by Voronoi diagram-based methods \cite{Medek2007Voronoi, Petrek2007MOLE, Yaffe2008MolAxis, Lindow2011Voronoi, Chovancova2012Caver3}.
These methods first compute a Voronoi diagram of the protein atoms and use the Dijkstra algorithm on top of it. 
Such an approach enables to save a huge amount of resources.
The resulting tunnel is then represented by a set of spheres positioned onto the Voronoi edges forming the tunnel centerline.
But the tunnel boundary is determined by the surrounding atoms so it is far from being spherical.
Therefore, this traditional spherical representation may lead to misinterpretation of the analyzed tunnel.
As a consequence some alternative methods combining the grid and Voronoi-based techniques appeared~\cite{Jurcik2015Visibility}.
These approaches detect the tunnel centerline using the Voronoi diagram and then rasterize the space around the centerline to obtain more precise representation of the tunnel surface.


Nowadays, the biochemists are focusing more on the analysis of simulations of molecular dynamics rather than on static molecules, as these techniques yield more biochemically relevant results.
Analysis and subsequent exploration of tunnel behavior in long molecular dynamics simulations is, however, still one of the biggest challenges.
%In order to analyze empty space inside highly dynamic environment such as proteins it is necessary to correctly track it over time. 
Nevertheless, there are already several tools which are able to process such simulations (e.g., \cite{Chovancova2012Caver3}).
In consequence, few approaches to their visual exploration appeared as well (e.g., \cite{Lindow2012DynamicChannels, Lindow2013DynamicCavities, Jurcik2016TransparentMolecularSurface}).
These methods focus on interactive 3D exploration of protein inner voids in real time.
However, they also suffer from problems related to 3D representation itself. 
Moreover, by using these techniques it is hard to capture the significant changes of tunnel shape or constitution over time.

For the thorough analysis of protein behavior, the physico-chemical properties of amino acids in tunnel vicinity are at least equally important as the geometrical aspects. 
Therefore, recently several techniques was proposed by Parulek et al.~\cite{Parulek2013CavityAnalysis} and by Byska et al.~\cite{Byska2015MoleCollar,Byska2015AnimoAminoMiner}. 
These techniques are using a high level of abstraction in order to depict the evolution of protein voids including the nearby amino acids in a single image.
However, when using a 2D view, the information about the influence of individual tunnel lining amino acids and their mutual positions is completely lost.
This problem is addressed by our proposed approach.

%There are tools capable of such tracking, for instance, CAVER~3.0~\cite{Chovancova2012Caver3}. 
%{\color{red}Moreover, this does not apply only to detection of protein tunnels but other protein voids as well.}
%Nevertheless, nowadays the needs of biochemists extend beyond a simple detection of the protein voids.
%Recently the focus shifted more in the direction of interactive exploration of the obtained data. 
%As an example we can mention the following methods~\cite{Parulek2013CavityAnalysis,Lindow2013DynamicCavities, Jurcik2016TransparentMolecularSurface} which focus on interactive exploration of protein cavities in real time.


%As already mentioned, for 
%Both of them focus on the investigation of the evolution of protein tunnel or its selected part and its surroundings over time.
%The first approach, called MoleCollar, uses multiple contours plotted over each other in order to communicate the changes in shape of a selected part of the tunnel (\eg its bottleneck which is the narrowest site). 
%The contour representation is enhanced by depicting the surrounding amino acids and their different biochemical properties.
%The second approach, called AnimoAminoMiner, is based on a similar concept but it provides more general overview of the shape of the whole tunnel and its surroundings.
%Here the shape of the tunnel is communicated using set of curves representing the width of the tunnel with respect to its length.
%This view is equipped with an abstracted 2D visualization representing the tunnel areas influenced by the surrounding amino acids.
%Both MoleCollar and AnimoAminoMiner techniques immediately convey the information about the stability of both geometric and physico-chemical properties of the observed tunnel.
%However, since both techniques are using a high level of abstraction in order to depict the evolution of protein tunnel including the nearby amino acids in a single image, they omit the mutual spatial orientation of the extracted amino acids.

\subsection{Projections, Reformations and Comparative Visualization Methods}
The core idea of our technique is based on unfolding the 3D tunnel surface to a 2D image in order to prevent the occlusion problems.
Moreover, such a reformation allows us to dedicate one of the dimensions to the requirements of comparative visualization. 
The similar approach is commonly used in other domains as well.

For example, Kretschmer et al.\cite{Kretschmer2014AnatomyDriveReformation} adapted a variant of as-rigid-as-possible reformation proposed by Liu et al.~\cite{Liu2008LocalGlobalMeshParametrization} for medical applications. 
The resulting method defines a reformation of volumetric data driven by particular geometry -- in this case the anatomy of a specific patient.
Another extension of the work of Liu et al. was presented recently by Brambilla et al.~\cite{Brambilla2016ComparativeVisTimeSufaces} who focus on so called time surfaces which are frequently used for the investigation of fluid flows.
The proposed method is using a reformed 2D space in order to observe an evolution of these complex surfaces over time.
Unfortunately, since all these methods are relatively general, they produce an inevitable distortion in the distance. 
This is unsatisfactory when comparing protein tunnels since here the main focus is placed on the tunnel length, bottleneck, the overall surface shape and the surrounding amino acids. 

In order to minimize the distortion as much as possible we can exploit the unique tubular shape of protein tunnels.
A similar approach was used, for instance, by Gurijala et al.~\cite{Gurijala2013Colon}.
They presented a method that produces a rectangular flattening of the colon model.
This method handles very well a topological noise and preserves the colon wall shape, which allows to easily observe the polyps (abnormal growth of tissue) inside the colon. 
The proposed normalized rectangle view, however, does not depict the radius of the colon.
This can be omitted in this particular use case of colon polyp detection, but it is essential when designing a comparative visualization of protein tunnels.

Another example of surface reformation of the tubular structures comes from the field of vessel visualization.
The Curved Planar Reformation (CPR)~\cite{Kanitsar2002CPR} is widely known technique commonly used for diagnosis of vascular diseases of peripheral arteries with single dominant direction.
In order to investigate the vessels of an arbitrary orientation, Mistelbauer et al.~\cite{Mistelbauer2012CP} proposed so called Centerline Reformations (CR).
The CR is an extension of CPR method but it uses a wavefront propagation of vessel centerline for automatic setting of the vector of interest.
Due to the nature of this particular reformation there is a trade-off between the visibility of the vessels and errors when depicting the surrounding tissue as context.
In order to overcome these problems, another variant of the CPR method was proposed by Auzinger et al.~\cite{Auzinger2013Vessel}. 
This method avoids the visibility issues of CPR and CR caused by the projection by computing the vessel lumen (empty space inside of a vessel) fully in 3D. 
This is done by finding a cut through the vessel and surrounding tissue orthogonal to the vessel centerline and view direction.
The view-dependency would, however, cause some issues in our case, since we are aiming for comparative visualization and hence we need to find the same cut for each tunnel in order to obtain a common space.
Moreover, the proposed cutaway discards a part of the vessel surface while we want to communicate the shape and biochemical properties of the whole protein tunnel.

There are several other examples in the literature regarding the comparative visualization of unfolded, or abstracted, tubular structures. 
For instance, Angelelli et al.~\cite{Angelelli2011StraighteningTubularFlow} presented a method for investigation of the flow through tubular structures. 
Lampe at al.~\cite{Lampe2009CurveCentric} on the other hand provided a solution for a curve driven analysis of general flow.  
Similarly to CPR, both methods are based on straightening of the volumetric data in the direction of the flow.
Such alignment allows to employ comparative visualization (\eg juxtaposition view), because one axis becomes shared between multiple instances (in this case between various snapshots of the flow simulation over time).
We are looking for a similar solution, but none of the mentioned methods can be used directly.
On one hand, the method proposed by Angelelli et al. is computing the reformation directly in the 3D space and hence it suffers from the occlusion issues.
On the other hand, while the method designed by Lampe at al. provides a great overall view of individual flow features, it does not preserve the shape nor angles of external objects.
In both cases it means that the at least some essential information about protein tunnel surface and its surrounding amino acids would be lost.


\section{Unfolding-Based Exploration}

As already stated, the main goal of our work is to allow an interactive exploration of molecular tunnels ensembles coming from molecular dynamics simulations or protein mutations.
In both cases a tunnel can develop and change its shape dramatically.
From the raw simulation data, we derive tunnels as a set of 3D objects representing the tunnel shape over time.
In case of mutations, we obtain a set in the identical form, the only difference is that it represents tunnel in one static time step but with different mutations of its surrounding amino acids.

In general, there is no trivial or a direct way to orient/position 3D representation of the tunnels for exploration of its similarities and dissimilarities.
There are several issues preventing direct comparison of such structures, e.g., the self-occlusion of tunnel features in 3D, and occlusion between multiple tunnels.
Moreover, there is always a limit of how many 3D objects users can explore at the same time in one window.
To overcome the problem of tunnel self-occlusion we unfold a 3D object to 2D representation to speed up the exploration of the similarities or dissimilarities.
However, molecular dynamics consists of thousands time steps and comparative visualization of shapes of all the tunnels, both 2D and 3D versions, is challenging.

To further simplify the process of comparing the tunnel structure, we employ a set of descriptors based on image moments.
These are applied on acquired images of unfolded tunnels.
Image moment is a well known descriptor for image analysis and classification.
To visualize and analyze results of the computed descriptors we further employ principal component analysis (PCA) for dimension reduction.
With PCA we can show the tunnels similarities/dissimilarities as a distance between two points in 2D domain.

Having multiple views, the interaction allows to explore the space of tunnels in 2D as a scatterplot and at the same time to compare spatial characteristics of the unfolded tunnels.

\subsection{Unfolding Process}
Each tunnel is defined by its shape as a triangle mesh, its centerline as a graph of connected points, and the information about hydrophobicity, charge, and hydrogen bonds of the tunnel-lining amino acids is stored for each vertex of the mesh.
Moreover, we have a set of characteristics that are of utmost importance to explore.
In our case we want to clearly communicate three features ordered from the most to the least important.
The first feature is the positioning and distribution of amino acids that form the tunnel boundary.
The second one is the spatial information about the tunnel length and its thickness development.
The third feature is the notion of the tunnel width meaning that the user should be able to detect narrower and wider areas of the tunnel.
Here the narrowest part of the tunnel, the bottleneck, is usually also the most important one because it determines the size of a ligand molecule which can follow this tunnel.

The general idea of our unfolding method is based on the centerline parametrization.
For each tunnel we have the centerline curve $\mathbf{c}(t) : [t_0, t_1]$ of the tunnel, and the cut direction $\mathbf{v}$.
Our method is based on slicing the tunnel by clip planes perpendicular to centerline tangent at position $\mathbf{c}(t)$ and sampling the slice by rays emerging from $\mathbf{c}(t)$ with the direction of the rotated cutting vector $\mathbf{v}$ around the centerline tangent by angle $a$.

The centerline is always inside the tunnel and does not exhibit any high curvatures.
However we are well aware, that two neighboring planes might cross.
Therefore the normal vector if the clip plane is an average vector of directions from approximately ten neighboring points on the centerline.
Which is sufficient enough for case of molecular tunnels \cite{Byska2015AnimoAminoMiner}.

The cutting vector $\mathbf{v}$ is semantically defined as a border point between two stable amino acids in the first several slices.
These stable amino acids can be found close to the tunnel end point which is deeply buried in the protein structure.
This is derived from the fact that the amino acids close to the protein surface are much more flexible than those densely packed inside.
This allows us to create one of the directions for the shared comparative visualization, as the neighboring amino acids are stable during all the simulation of the dynamics.
There are several other ways the cutting vector might be defined, but for our current needs this setting is sufficient. 
For instance, one might come up with more semantically correct cut, which would follow the borders between the neighboring amino acids.
%This approach would not suffer from artifacts such as cutting one amino acid into two parts which can happen in our solution \todo[color=blue!40]{{\color{black}not sure whether we should mention also this}} .

Having a tangent of the centerline and the global slicing vector can introduce a rotation artifact of the cut. 
To overcome this problem, for each cutting plane along the centerline we project the cutting vector to the plane.
 
Shape overlays that are the result of the cuts are uniformly sampled.
It is possible that between two neighboring samples some information might be lost, for example a small connecting cavity.
However, this structure is too small to have any impact on the protein, and therefore we decided not to take this feature into account.
The sampling is performed using the ray coming from the centerline and increasingly rotated around the slice normal.
At each sample we compute a distance between the sample and centerline, and a slice line length between two samples $D(a_i, a_{i+1})$, where $a_i$ and $a_{i+1}$ are two neighboring samples(see Figure~\ref{fig:unfolding}).

\begin{figure}[htb]
\includegraphics[width=\linewidth]{img/unfolding_in_out.jpg}
\centering
\caption{
We cut the tunnel along its centerline. Then for each point on the centerline we create one slice.
By straightening the cuts and putting them on top of each other we unfold the tunnel.}
\label{fig:unfolding}
\end{figure}

For each sample, in every slide we compute a new coordinates.
First coordinate is based on the parameter $t$. The value of the parameter ranges from 0, to the length of the centerline, and it is a distance along it. 
Second coordinate system is computed from the second parameter $a$. 
Due to fact, that parameter $a$ is sampled uniformly, and for each neighbors we store a distance $D(a_i, a_{i+1})$, we are able to compute a size of the surface slice as a sum $\sum_{l=0}^{36} D(a_l, a_{l+1})$.
Because we are doing an unfolding, samples from the cut should be on side, and samples from the opposite direction ($180^{\circ}$ with $a=18$).
For unfolding a tunnel to coordinates, where the first one is for the length in centerline and second for the length in the cut the coordinates would be:\begin{equation}
(t, \sum_{l=0}^{j} D(a_l, a_{l+1}) - \sum_{l=0}^{18} D(a_l, a_{l+1})).
\end{equation} 

Thus, our unfolding method allows us to encode tunnel surface values in 2D.
Moreover, the size of the tunnel over the centerline is preserved, as well as the size and position of the amino acids around the surface and their respective neighborhood.

By connecting the same angle samples together we get a shape description that communicates the changes of the tunnel shape.
For example, at the place where the lines are dense the tunnel is narrower.
On the other hand, more scattered lines signify that the tunnel is wider (see Figure~\ref{fig:flatteningUtility}).

\begin{figure}[htb]
\includegraphics[width=0.9\linewidth]{img/debugger.png}
\centering
\caption{
An illustration of the connection between tunnel 3D shape, its unfolded representation, and tunnel slicing. The unfolded representation resembles a map where each region corresponds to one amino acid. The density of the horizontal curves helps to understand the tunnel width.
}
\label{fig:flatteningUtility}
\end{figure}

For illustration purposes we also prepared a utility (see Figure~\ref{fig:flatteningUtility}) to show the spatial connection between the representations.
The utility is quite useful to get a grasp of the tunnel properties, to evaluate the correctness of the unfolding process, and to demonstrate the ability of the representation to show important features.

Nevertheless, the core benefit of the unfolded tunnel representation lies in the ability to perform a comparative visualization.
Juxtapositioned or superpositioned of the unfolded tunnels give an overview of the spatial and content-wise differences between different tunnels.

Note that in case of a smaller number of tunnels a simple composition of comparative visualization is sufficient.
However, when analyzing molecular dynamics simulations one can obtain hundreds of time frames that are considered crucial.
As the tunnel develops over time, together with the whole molecule, it changes its shape and content.
Moreover, the tunnel properties change over time as well.
To show the similarity/dissimilarity of tunnels one needs to have a suitable descriptor of a single instance.
Since the unfolded representation contains all the relevant information in 2D, i.e. forming an image, we opted for image moments as the main set of descriptors.

\begin{figure*}[htb]
\includegraphics[width=\linewidth]{img/processing_pipeline.jpg}
\centering
\caption{Processing pipeline.
Each tunnel (a) is unfolded (b), described with image moment, and processed to 2D point of similarity overview (c).
At the end the tunnels are shown in multiple views(d). }
\label{fig:processing_pipeline}
\end{figure*}

\subsection{Image Moment}
Image moments~\cite{Flusser09Moments} provide a practical and useful way to describe image objects. 
Each image $I(x,y)$ is described by the set of moments
\begin{equation}
M_{ij} = \sum_{x}\sum_{y}x^iy^j I(x,y)
\end{equation} 
There exist various versions of image moments, which would bring invariance to different properties, such as rotation, scale, or translation.
For example, centralized moments are invariant to translation, which is a valuable property since some amino acid areas might change their longitudinal position with respect to the length of the centerline.
Centralized image moments for an image $I(x,y)$ are defined as
\begin{equation}
\mu_{ij} = \sum_{x}\sum_{y}\left(x - {M_{10} \over M_{00}}\right)^i\left(y - {M_{01} \over M_{00}}\right)^jI(x,y)
\end{equation} 
This way we are able to specify each tunnel as a vector of values with the central moments of order up to three to condense the information.
In our case, for the tunnel image $I$, it would be a vector $I_m$ of ten different image-centralized moments.
\begin{equation}
I_m = (\mu_{00}, \mu_{01}, \mu_{10}, \mu_{11}, \mu_{02}, \mu_{20}, \mu_{12}, \mu_{21}, \mu_{03}, \mu_{30})
\end{equation} 
Image moments also maintains the property that similar images have similar values.
In consequence, distinct images have more distant values, so we can transform the similarity between images to distance between the image moment vectors.
Having such a database of tunnel vectors, we can use the standard tools of information visualization to get the idea about the distances between tunnels.

\subsection{Similarity Overview}
We are able to set up a $m$-by-$n$ tunnel matrix $IM$, whose rows, $m$, consist of the centralized image moment vectors $I_m$ for each tunnel.
%\begin{equation}
%IM = 
%\begin{pmatrix}
%I_m(tun_1) \\
%I_m(tun_2) \\
%\vdots    \\
%I_m(tun_m) 
%\end{pmatrix}
%\end{equation} 

When dealing with a tunnel in molecular dynamics, the matrix $IM$ contains hundreds of rows and it is challenging to explore the raw matrix to see and understand which tunnels are close to each other and which are not.
To make the ensemble more understandable, we project the $IM$ matrix of tunnel image moments to 2D, where each 2D point represents one tunnel.
Here, the important requirement is that the distance between the tunnels in the matrix must be transformed into the distances between points.

First, the matrix dimension needs to be reduced.
There are several approaches for dimensionality reduction, such as Principal Component Analysis(PCA), Kernel Principal Component Analysis(KPCA)~\cite{Kim2005KPCA}, Independent Component Analysis (ICA)~\cite{Olshausen1997ICA}, t-Distributed Stochastic Neighbor Embedding (t-SNE)~\cite{mateen2008tsne} and others.
The important property of the approach is the ability to reduce the ten digits tunnel descriptor to 2D point coordinates and to visualize the statistical results for the whole matrix.
Visualizing statistical results can help to identify clusters and outliers as well as to analyze deviation, distribution, and correlation. Because most of the approaches produces similar result, and for its simplicity, we have adopted PCA for dimension reduction.

PCA is a statistical tool that transforms a set of observations, in our case a set of image moment vectors, to the set of linearly uncorrelated variables. 
Each of the resulting components is orthogonal to each other and the number of components is lower, or equal, than the number of the original variables.
The components are ordered by the variance value.
Meaning that the first component has the largest possible variance and each succeeding component has a lower variance.
In our overview, we showcase the first two PCA components for the tunnel, which are encoded in the coordinates.
The first component value encodes the $x$ coordinate, and the second encodes the $y$ coordinate (see Figure~\ref{fig:processing_pipeline}).

Natural image statistics were deeply analyzed by Fang et al.~\cite{Fang2013NaturalImageStatistics}, where the authors have designed new visualizations for image statistics.
Our 2D overview is just a simple demonstration, however, more complex visualization method can be used instead, for example Combined design~\cite{Fang2013NaturalImageStatistics} to show the parameters of PCA and Gabor descriptors at the same time.
This is one of the possible future directions of the method.

\subsubsection{Clustering}
Having the visual representation of the similarity between tunnels is a very useful tool for the navigation through possible tunnel arrangements, which was shown, and discussed in the work of van den Elzen et al.\cite{Elzen2016SnapshotsToPoints} on the example of dynamic networks.
With points spread in the 2D space it is easy to see where the points are more densely populated (clusters) and which points are more distant from other ones (outliers).
However, for a successful connection with other views, one needs a proper color depiction of clusters and outliers.
Here, clustering allows us to make groups of points to determine patterns in the overview.
%Clustering has its advantages when the data set is defined and a grouping needs to be determined from it.
%Essentially, points in a cluster determine a group of similar tunnels.
%A general open question for a successful cluster set is a number of clusters to determined in advance.
%For a user without any prior knowledge about the data, this might be difficult.

There are different clustering algorithms that could be applied, for example hierarchical clustering, or k-means approaches. 
In k-means clustering the number of clusters is fixed to $k$ and needs to be specified in advance, which is considered to be one of the main drawbacks of this algorithm.
On the other hand, hierarchical clustering do not need the number of clusters in advance.
In our case, we would like to show an unfolded representative from each cluster.
As this representation requires available space in window, the number of unfolded tunnels is limited.
We have empirically found out that showing five tunnels at the same time is the limit that also gives us a suitable amount of clusters for k-means clustering, which transforms a k-means drawback to our advantage.
Moreover k-means was selected because of its simplicity and for its conceptual closeness to the nearest neighbor classification.
However, a well known problem relates to the borders of clusters, since the algorithm optimizes cluster centers, not cluster borders. This represents another direction of our future work, where we will conduct experiments with other families of cluster algorithms such as hierarchical clustering, density clustering, and other methods from machine learning.

Additionally, it is also important to mention the right choice of distance metric for the clustering algorithm. 
Here, the Euclidean distance represents the natural choice, which is also very easy to work with.
However, it is not that straightforward to see its application to the image moment descriptor as well.
More appropriate might be to use the Mahanalobis distance.
The Mahalanobis distance is a measure of the distance between a point and a distribution.
The Mahalanobis distance is unitless and scale-invariant and takes into account the correlations of the data set.

Image moment descriptor, dimension reduction, and clustering should all bring the same notion of tunnels similarity/dissimilarity.
The original image moment is not invariant to translation, rotation, or scale, but there exist versions in which those properties are invariant.
We have decided to use the centralized image moment, as it is invariant to translation because all the tunnels have the same rotation and uniform scaling.
Translational invariance helps us with the problem of translated amino-acids, due to the change of the centerline length.
As can be seen in Figure~\ref{fig:invariance}, we tested the generation of the overview scatterplot with four different ways of generating the value, which are: standard, tunnels rotated, tunnels scaled, and tunnels colored by the different color scheme.
We can see that even though the positional distribution of the points differs, the notion of cluster and two outliers is preserved in all the different ways of generating image moment values.
Moreover, the important aspect here is that for the overview scatterplot we have a shared space which allows us to see the neighborhood of the tunnels, which is our requirement for employing comparative visualization as a part of the exploration process.

\begin{figure}[htb]
\includegraphics[width=0.8\linewidth]{img/invariance.png}
\centering
\caption{
Tunnel similarity overview for four different ways of generating image moment: standard (upper-left), with amino acids coloring permutation (upper-right), rotated (lower-left), and with normalized size of the centerline (lower-right).
Points are colored according to the detected clusters.
}
\label{fig:invariance}
\end{figure}

\subsection{Exploration}

Until now we described individual parts of our exploration solution.
All of them play a crucial role in the exploration process.
Therefore, our final exploration solution consists out of these views (see Figure~\ref{fig:processing_pipeline}d).
First is a view of the set of unfolded tunnels, which allows to make a comparison of spatial and structural aspects of the tunnel.
Second is the scatterplot showing the similarity/dissimilarity overview which brings forth the notion of the differences between tunnels.
And finally is the bar chart view where each tunnel is represented by one bar and the height of the bar corresponds to the tunnel length.

\begin{figure*}[htb]
\includegraphics[width=\linewidth]{img/5dynamics.pdf}
\centering
\caption{Visualization of sequence of 350 time steps of DhaA haloalkane dehalogenase protein. The bar chart shows the tunnel stability while the scatterplot provides an information about different outliers. The unfolded representation then depicts the influence of individual amino acids.}
\label{fig:dynamic}
\end{figure*}

Using the unfolding tunnel view the user is able to intuitively compare the width of the tunnels, the position of their bottleneck, the set of tunnel-lining amino acids and their extent of influence.
In order to communicate various physico-chemical properties of individual amino acids we use color mapping. 
However, using this approach we are able to visualize only a single property at once.
Hence we provide also more aggregated view situated next to the unfolded tunnel image.
This view communicates the average value for each observed physico-chemical property computed for the tunnel-lining amino acids.

The unfolded tunnels are positioned side by side, or in other words by using the juxtaposition composition.
Positioning tunnels from different time frames allows the user to see the behavior of the bottleneck as well as the amino acids.
It is visible that the unfolded tunnels need a space to be seen properly.
Therefore, in order to see the tunnels in this view in full detail it is appropriate only for a limited number of tunnels.
We have empirically found out that five tunnels is the limit for the resolution width 1900.
If more tunnels should be visualized, they need to be additionally downscaled, which means that with more tunnels more spatial details are discarded and the visual representation has to be scaled.


To show the dataset of hundreds of tunnels from the molecular dynamics simulation, it is unfeasible to use the unfolding view to get the overview information about tunnel changes.
Easily shown in an example -- with the resolution width 1900 and more than 1900 tunnels we would have more unfolded tunnels than available pixels.
Therefore, we have constructed a similarity overview which allows us to code one tunnel as a point.
Having here too many tunnels is still feasible as we are here more interested in tunnels similarity/dissimilarity represented by a groups/outliers.

The last missing link is to have an overview of the tunnels with respect to time.
This requirement led us naturally to the bar chart representation, where the height of bars correspond to the tunnel length.
This way we have a view which allows us to have a unique and well distinguishable representation for each tunnel.

The real power of the exploration lies in the possibility of brushing between the similarity overview (scatterplot) and tunnel length view (bar chart). 
Selecting one point in the scatterplot highlights the corresponding tunnel in the bar chart and shows the unfolded content of the tunnel.
Of course, this selection works also in the opposite direction when selecting a bar highlights the corresponding point in the scatterplot in order to easily recognize if the tunnel has a stable shape or if it is an outlier.

In overall, the user has the power to explore the spatial and content-wise aspects of the tunnels by selecting the desired tunnels in the bar chart and the scatterplot.
Thanks to the bar chart it is possible to visualize the tunnel development over time and scatterplot helps to explore the similarity of the tunnel and to spot the outliers.

\section{Evaluation}
To demonstrate the usability of our approach we conducted two case studies following the research of our cooperating researchers from the field of protein engineering. 
The first study deals with exploration of simulations of molecular dynamics and the second study focuses on scrutinizing the tunnel shape modified by mutations of a selected tunnel-lining amino acid.

\begin{figure*}[htb]
\includegraphics[width=\linewidth]{img/mutaceExample.png}
\centering
\caption{Visualization of different mutations of the amino acid with ID 176 (highlighted in green) surrounding the main tunnel in DhaA haloalkane dehalogenase. The scatterplot and bar chart show the information about all tunnels in the dataset whereas the unfolded representation shows only one selected representative of each detected cluster. The amino acid is highlighted for better comparison.
}
\label{fig:mutation}
\end{figure*}


\subsection{Exploration of Molecular Dynamics}
In this case the task is to explore and evaluate a single tunnel in each time step (or a selected subset) of molecular dynamics simulation.
We first derive the unfolded 2D representation and these images are subsequently scrutinized to reveal similarities between them. 
This produces clusters of tunnels according to their similarity which are visualized using the scatterplot.
Additionally, the coloring of individual clusters helps us to find the correspondence between the scatterplot and the bar chart representation where we can see the positions of tunnels belonging to these clusters spread over time. 
The bar chart immediately shows the time portions in which the tunnel was stable or unstable (depending of the interest of the researcher).
Figure~\ref{fig:dynamic} shows the resulting representation for a sequence of 350 time steps of DhaA haloalkane dehalogenase protein.
From the bar chart view we can clearly see that the tunnels shape is highly stable in the first part of the simulation while it becomes more and more unstable towards the end. 
On the other hand, from the unfolded representation, containing by default the most representative samples of individual clusters, it is obvious that during the stable period (clusters \#2 and \#4) there was almost no influence of Tyrosine (Y:259 highlighted by red). 
This changes later when also the influence of the neighboring amino acids, such as Phenylalanine F154 and Asparagine N27 is starting to change significantly.
Moreover, using our tool, the biochemists were immediately able to spot several outliers belonging to the cluster \#3 (see vertical arrows in bottom of Figure~\ref{fig:dynamic}). 
This cluster represents tunnels which are significantly shorter then others.
The same cluster can be also easily identified in the similarity overview where this whole cluster is clearly separated from the rest (see white circle in Figure~\ref{fig:dynamic}).

By clicking on the individual bars in the bar chart the user can select a subset of tunnels to be explored in more detail.
These selected time steps are immediately visualized using the unfolded representation and the tunnels are juxtaposed to enable the comparison of the width and constitution of the tunnel.

The biochemists testing our approach confirmed that the first main benefit is in the navigation phase where they were able to immediately spot the time steps with significant tunnel changes which are usually the best candidates for further exploration.
In the subsequent exploration phase using the unfolded view they appreciated the information about the area of influence of the amino acids and their mutual position. 
Some of them were slightly confused about the fact that some amino acids are divided by the cut into two parts which makes the comparison task more complicated.
However, this can be solved by interactive manipulation with the cut position or in the future also by introducing more sophisticated method for defining the cut.
But in summary they confirmed that this tool has a high potential for this type of tasks.

\subsection{Exploration of Tunnel Mutations}
One of the research topics conducted by the cooperation group of protein engineers is dealing with engineering protein stability and resistance to organic cosolvents~~\cite{Koudelakova2013StabilityAndResistance}.
This is reached by mutating the amino acids around the main tunnel of the DhaA haloalkane dehalogenase protein molecule. 
The paper first presents the confirmation of importance of the amino acids surrounding the tunnel by presenting the results of several mutations of amino acids on different places in the molecule.
It was revealed that by mutating only the amino acids in the close vicinity of the main tunnel the researchers were able to change the stability and resistance of the protein substantially.
Then it presents the study in which the biochemists aimed to find the best possible mutation around the main tunnel which would increase the stability of the dehalogenase and its resistance to organic cosolvents.
The researchers revealed that the DhaA80 mutation in which the amino acid on position 176, which in the wild type form contains Cysteine, was replaced by Phenylalanine.
This mutation closed the main tunnel which caused the increase in melting temperature of the protein by 19 degrees and the resistance to cosolvent dimethyl sulfoxide was increased 4000 times.
This situation is clearly visible in our representation as well.
Figure~\ref{fig:mutation} demonstrates the situation when we performed multiple mutations of a single amino acid in position 176 in the protein chain.
It is obvious that if the original amino acid (
Figure~\ref{fig:mutation} -- CYS) is replaced by similar or even a smaller one, such as Glutamic Acid or Glycine (Figure~\ref{fig:mutation} -- GLU and GLY respectively) the tunnel becomes wider.
On the other hand, using bigger amino acids, such as Phenylalanine or Histidine (Figure~\ref{fig:mutation} -- PHE and GLY respectively) decreases the bottleneck of the tunnel significantly.
This corresponds exactly to the outcomes of the real in-vitro experiments which were conducted by the biochemists.

When evaluating the suitability of our approach to this type of tasks the biochemists appreciated the unfolded view much more than in the case of molecular dynamics simulations.
Here the information about the changes on the tunnel surface and its width caused by the mutations is crucial and it is clearly visible from our representation. 
Moreover, in this particular case when the user is interested in a specific amino acid, our tool enables to highlight it in order to even enhance the comparison.
The biochemists confirmed that similar information is very hard to understand from 3D tunnel representation, namely when aiming to compare more than two or three mutated tunnels at once.
Therefore, they appreciated our representation and suggested its future extension by calculating and highlighting areas with the most significant changes.

\section{Conclusion \& Future work}
We have presented a novel method to explore the shape and content of ensembles of tunnels in protein molecules.
Our approach consists of transforming 3D shape to more readable 2D unfolded representation, using image moment as a descriptor for each tunnel, and providing multiple views on the tunnel data to promote the exploration process.
The resulting system can interactively show the overall development of the tunnel centerline, the tunnel similarities and dissimilarities, and the shape and content of a selected set of tunnels.

We demonstrated the usage of the method in two case studies from the field of biochemistry which were also commented by the domain experts.
This confirmed that our method can be used for the time-dependent data as well as for the datasets containing tunnel mutations.

After the discussions with the domain experts we also suggest several possibilities for future extensions. 
They are related to the unfolding process, generating tunnel similarity measure, and final visualization of the dataset.
Regarding the unfolding we discussed a possibility to have a more intelligent cutting mechanism enabling more semantically-driven cut that would follow the borders of the amino acids in the tunnel.
For the similarity overview, it is worthwhile to try the combination of image moment, reduction, and clustering, that is invariant to amino acids color permutation, rotation, and scale.
The invariant method would allow to compare even two different settings of two different data sets.
There were also some new ideas of the final visualization composition.
First was to incorporate the unfolded overview for the whole cluster.
This means to visualize the clusters side by side, where each cluster would not be seen by one representative, but rather by the variance visualization showing the stability of the cluster.

%\todo{this sounds strange}
%Extending this concept to the whole molecule, our collaborators suggested that the whole molecule unfolding would be beneficial to visualize and explore in a similar manner.
%\todo{not sure whether it is not there already, but we should mention the limitation of the algorithm - \eg it does not handle cases when there is a hole inside the tunnel mesh}


\section{Acknowledgement}
This work was supported through grants from the Norway grants project NF-CZ07-MOP-2-086-2014, and the PhysioIllustration research project 218023 funded by the Norwegian Research Council.

%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}

%-------------------------------------------------------------------------
\newpage


\end{document}
