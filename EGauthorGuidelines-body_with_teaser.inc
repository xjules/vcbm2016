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
In this paper we introduce a novel approach to the comparative visualization and exploration of ensembles of tunnels
We aim to overcome the occlusion problems of traditional tunnel representations and to quickly navigate the user through the input dataset and help to identify the possibly interesting tunnels.
First, we unfold the input tunnels to a 2D representation enabling to observe the mutual position of amino acids forming the tunnel surface and the amount of surface they influence.
These 2D images are subsequently compared using the image moment method commonly used in image processing.
This way we are able to detect similarities and outliers in the dataset which are visualized as clusters in a scatterplot graph.
The same coloring scheme is used in the linked bar chart enabling to detect the position of the cluster members over time.
These views help to select a subset of possibly interesting tunnels which can be further explored in detail using the 2D unfolded view and traditional 3D representation.
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
The user is overwhelmed by the movements and the differences in the tunnel shape can be easily overlooked.
Moreover, using the 3D tunnel representation only a portion of the tunnel surface is visible from the viewpoint.
When aiming to explore a tunnel influenced by several mutations of its surrounding amino acids, the user wants to observe and evaluate the impact of these mutations on the tunnel surface. Using superposition of the mutated tunnels we suffer from visual clutter caused by surface overlaps (see Figure~\ref{fig:tunnels} left).
These overlaps can be removed by using juxtaposition of the tunnel representations (see Figure~\ref{fig:tunnels} right).
But such a case is applicable only on a small set of objects because it can be hard to perceive the differences between them, namely for those in further mutual distance. 
This problem is even stressed when using the 3D tunnel representation.

\begin{figure}[htb]
 \includegraphics[width=\linewidth]{img/tunnels.png}
 \centering
  \caption{Left: superposed representation of five conformations of a tunnel differing by one mutated amino acid. Right: juxtaposed view of these conformations.}
\label{fig:tunnels}
\end{figure}

Moreover, the proper visualization of surface itself is not sufficient for exploration and complete understanding of differences between protein tunnels. 
Another essential information is about the amino acids forming the tunnel boundary, namely their biochemical properties and the extent of influence of the tunnel.
Possible solution is to map this information onto the tunnel surface.
But because of the problems with the 3D tunnel visualization mentioned above, it is hard to compare and explore these properties as well.

In this paper we are aiming to solve these problems by introducing a novel technique for intuitive comparison and exploration of ensembles of protein tunnels.
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

As already mentioned, the biochemists are more and more focusing on the analysis of simulations of molecular dynamics rather than on static molecules, as these techniques yield more biochemically relevant results.
In order to analyze tunnels inside such a dynamic environment it is necessary to correctly track them over time. 
There are tools capable of such tracking, for instance, CAVER~3.0~\cite{Chovancova2012Caver3}. 
%{\color{red}Moreover, this does not apply only to detection of protein tunnels but other protein voids as well.}
Nevertheless, nowadays the needs of biochemists extend beyond a simple detection of the protein voids.
Recently the focus shifted more in the direction of interactive exploration of the obtained data. 
As an example we can mention the following methods~\cite{Parulek2013CavityAnalysis,Lindow2013DynamicCavities, Jurcik2016TransparentMolecularSurface} which focus on interactive exploration of protein cavities in real time.

As already mentioned, for the analysis of protein tunnels the physico-chemical properties of amino acids in the vicinity of the tunnel are at least equally important as its geometrical aspects. 
Therefore, recently two techniques by Byska et al.~\cite{Byska2015MoleCollar,Byska2015AnimoAminoMiner} appeared. 
Both of them focus on the investigation of the evolution of protein tunnel or its selected part and its surroundings over time.
The first approach, called MoleCollar, uses multiple contours plotted over each other in order to communicate the changes in shape of a selected part of the tunnel (\eg its bottleneck which is the narrowest site). 
The contour representation is enhanced by depicting the surrounding amino acids and their different biochemical properties.
The second approach, called AnimoAminoMiner, is based on a similar concept but it provides more general overview of the shape of the whole tunnel and its surroundings.
Here the shape of the tunnel is communicated using set of curves representing the width of the tunnel with respect to its length.
This view is equipped with an abstracted 2D visualization representing the tunnel areas influenced by the surrounding amino acids.
Both MoleCollar and AnimoAminoMiner techniques immediately convey the information about the stability of both geometric and physico-chemical properties of the observed tunnel.
However, since both techniques are using a high level of abstraction in order to depict the evolution of protein tunnel including the nearby amino acids in a single image, they omit the mutual spatial orientation of the extracted amino acids.

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

\subsection{Flattening and Unfolding Techniques}
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

\subsection{Comparative Visualization}
There are several other examples in the literature regarding the comparative visualization of unfolded, or abstracted, tubular structures. 
For instance, Angelelli et al.~\cite{Angelelli2011StraighteningTubularFlow} presented a method for investigation of the flow through tubular structures. 
Lampe at al.~\cite{Lampe2009CurveCentric} on the other hand provided a solution for a curve driven analysis of general flow.  
Similarly to CPR, both methods are based on straightening of the volumetric data in the direction of the flow.
Such alignment allows to employ comparative visualization (\eg juxtaposition view), because one axis becomes shared between multiple instances (in this case between various snapshots of the flow simulation over time).
We are looking for a similar solution, but none of the mentioned methods can be used directly.
On one hand, the method proposed by Angelelli et al. is computing the reformation directly in the 3D space and hence it suffers from the occlusion issues.
On the other hand, while the method designed by Lampe at al. provides a great overall view of individual flow features, it does not preserve the shape nor angles of external objects.
In both cases it means that the at least some essential information about protein tunnel surface and its surrounding amino acids would be lost.


\section{Flattening Based Exploration}
\begin{figure*}[htb]
\includegraphics[width=\linewidth]{img/processing_pipeline.jpg}
\centering
\caption{Processing pipeline.
Each tunnel is unfolded, described with image moment, and processed to 2D point of similarity overview.
At the end the tunnels are shown in multiple views. }
\label{fig:processing_pipeline}
\end{figure*}
One of the main goals of our work is to allow exploration of molecular tunnels in molecular dynamics simulation.
Over the course of simulations, a tunnel develops while its shape can change dramatically.
From the raw simulation data we derive tunnels as a set of 3D objects representing the tunnel shape over time.
In general, there is no trivial or a direct way to orient/position 3D representation of the tunnels for exploration of its similarities and dissimilarities.
There are several issues preventing direct comparison of such structures, e.g., the self-occlusion of tunnel features in 3D, and occlusion between multiple tunnels.
Moreover there is always a limit of how many 3D objects users can explore at the same time in one window.
To overcome the problem of tunnel self-occlusion we transform a 3D object to 2D representation by flattening.
Here the spatially reduced flattened tunnels ease and speed up the exploration of the similarities, or dissimilarities.
However molecular dynamics consists of thousands time steps.
Therefore, comparative visualization of shapes of all the tunnels, both 2D and 3D versions, is challenging.
To further simplify the process of comparing the tunnel structure, we employ a set of descriptors based on image moments.
These are applied on acquired images of unfolded tunnels.
Image momentum is well known descriptor for image analysis and classification.
To visualize and analyze results of the computed descriptors we employ PCA for dimension reduction.
With PCA we can show the tunnels similarities/dissimilarities as a distance between two points in 2D domain.
Having multiple view, with interaction allows to explore the space of tunnels in 2D as a scatter-plot and at the same time to compare spatial characteristics of the unfolded tunnels.
\subsection{Flattening}
Each tunnel is defined by its shape as a triangle mesh, a centerline as a graph of connected points, and information about tunnel hydrophobicity, charge, and hydrogen bond stored for each vertex of the triangle mesh.
Moreover, we have a set of characteristics, that are of utmost importance to explore.
In our case we want to clearly communicate three features ordered from the most to the least important.
First one is the positioning, and distribution of amino acids, which creates the tunnel.
Second is the spatial information of the tunnel length, and its thickness development.
Third feature is the notion of shape. 
Meaning that user should be able to detect {\color{red}{"bulky"}} areas.

\begin{figure}[htb]
\includegraphics[width=\linewidth]{img/unfolding_in_out.jpg}
\centering
\caption{
We cut tunnel along the centerline.
Each slice is additionally sampled around the centerline point.
By straightening the cuts, and putting them on each other we are unfolding the tunnel.}
\label{fig:processing_pipeline}
\end{figure}

The general idea of our flattening method is the parametrization.
For each tunnel, we have the centerline curve $\mathbf{c}(t) : [t_0, t_1]$ of the tunnel, and the cut direction $\mathbf{v}$.
Our method is based on the slicing of the tunnel by the plane perpendicular to centerline tangent at position $\mathbf{c}(t)$, and sampling the slice by the rays coming from the $\mathbf{c}(t)$ with the direction of the rotated cutting vector $\mathbf{v}$ around the centerline tangent by angle $s$.

The key point is the centerline.
Our assumption, based on the empirical knowledge is, that the centerline is alway inside the tunnel and that the centerline do not have high curvature.
Which means that two neighboring planes do not cross each other.

Cutting vector is semantically defined as a border point between two stable amino acids in first several slices.
This allows us to create one of the directions for the shared comparative visualization, as the neighboring amino-acids are stable during all the simulation of the dynamics.
For our current needs this setting of cutting vector is enough. However one might come up with more semantical cut, which would follow the borders between the neighboring amino acids.

Having a tangent in centerline and global slicing vector can introduce rotation artifact of the cut. 
We have a adopted a computation of rotation minimized frame \cite{Wang2008RotMinim}.
To overcome this problem for each cutting plane along the centerline is the cutting vector projected to the plane.

With settled the cutting plane, and cutting vector for each plane, we have a starting point, which is smooth, and follows the centerline on the surface of the tunnel. 
Cuts along the centerline are uniformly sampled.
It is possible, that between 2 cuts some information is lost, for example a small connecting cavity.
However this structure is too small to have any influence on the lipid, and therefore it is desired to have this feature abstracted out.

As mentioned earlier, each slice is additionally sampled.
Sampling is done by the ray coming from the centerline and increasingly rotated around the slice normal.
At each sample we now have a value, and we have a slice line length between two samples $D_t(a_i, a_{i+1})$.
Unfolding is defined as
\begin{equation}
A(t, a_j) = (t, \sum_{l=0}^{j} D(a_l, a_{l+1}) - \sum_{l=0}^{18} D(a_l, a_{l+1}))
\end{equation} 

With our unfolding method we have in 2D encoded values from the tunnel surface.
Moreover, the size of the tunnel over the centerline is accurately preserved, as well as the size of the amino acids from the surface and their respective neighborhood.

Connecting the same angle samples together we get a shape description, which communicates the changes of the tunnel shape, for example at the place where the lines are dense the tunnel is thinner.
On the other hand more scattered lines says, that the tunnel is broader.

\begin{figure}[htb]
\includegraphics[width=\linewidth]{img/debugger.png}
\centering
\caption{
Small utility showing a connection between tunnel 3D shape, its unfolded representation, and tunnel slicing.
}
\label{fig:flatteningUtility}
\end{figure}

Constructed unfolded tunnel gives us clear picture of its shape, and content.
Just for the demonstration part we have also prepared a small utility (see Figure~\ref{fig:flatteningUtility}) to show the spatial connection between the representations.
The utility is quite useful to get a good grasp of the tunnel properties, to evaluate the correctness of the unfolding process, and to demonstrate the ability of the representation to show important features.

Real usefulness of the unfolded tunnel representation is in the comparative visualization.
Juxtapositioned, or superpositioned, unfolded tunnels give an overview of the tunnel behavior over time, or spatial, and content-wise, differences between the different tunnels.

For some smaller number of tunnels simple composition of comparative visualization is enough.
However in usual output of the molecular dynamics one can have hundreds of interesting time frames.
As tunnel develops over time, together with the whole molecule, it changes its shape and content.
Tunnel can develop similar properties over time.
For the similarity/dissimilarity measure of the tunnels one needs to have a proper descriptor of the single instance.
Since unfolded representation holds all the relevant information, and is in 2D, we found it useful to use image moment as a descriptor.

\subsection{Image Moment}
Image moments~\cite{Flusser09Moments} provide a practical and useful way to describe image objects. Each image $I(x,y)$ is described by the set of moments
\begin{equation}
M_{ij} = \sum_{x}\sum_{y}x^iy^j I(x,y)
\end{equation} 
There exist various versions of image momentum, which would bring invariance to different properties such as rotation, scale, translation.
For example, centralized moments are invariant to translation.
This is a valuable feature, as some amino acid areas might me moved by the change of the length of the centerline.
In our case, images containing flattened tunnels are further characterized by 10 different image centralized moments to condense the information.
\begin{equation}
\mu_{pq} = \sum_{m}^{p}\sum_{n}^{q}{p \choose m}{q \choose n}\left(-{M_{10} \over M_{00}}\right)^{(p-m)}\left(-{M_{01} \over M_{00}}\right)^{(q-n)}
\end{equation} 
This way we are able to specify each tunnel as a vector of values.
\begin{equation}
I_m(tun) = (\mu_{00}, \mu_{01}, \mu_{10}, \mu_{11}, \mu_{02}, \mu_{20}, \mu_{12}, \mu_{21}, \mu_{03}, \mu_{30})
\end{equation} 
Image momentum holds a property, that similar images have a close values.
An in opposite, more different images have a more distant values, transforming similarity between the images to distance between the vectors.
With build up database of tunnel vectors, we can use the standard tools of information visualization to get an idea of the distances between the tunnels.

\subsection{Similarity Overview}
We are able to set up an $m$-by-$n$ tunnels matrix $IM$, whose rows, $m$, consists of the centralized image momentum vectors
\begin{equation}
IM = 
\begin{pmatrix}
I_m(tun_1) \\
I_m(tun_2) \\
\vdots    \\
I_m(tun_m) 
\end{pmatrix}
\end{equation} 

For examples of tunnel dynamics matrix $IM$ will have hundreds of rows and it will be challenging to explore the raw matrix to see which tunnels are close to each other and which not.

To make the ensemble more understandable we have decided to transform $IM$ to point set representation in 2D, where each point would depict one tunnel.
Another important requirement is that the distance between the tunnels in matrix must be truthfully transformed into distances between points.

Firstly, the matrix dimension needs to be reduced.
In our project we have adopted a simple solution of principal component analysis (PCA).

PCA is a statistical tool that transforms a set of observations, in our case set of image moments vectors, to the set of linearly uncorrelated variables. 
Each of the resulting components are orthogonal to each other, and the number of components is lower than the number of the original variables.
Moreover the components are ordered by the variance value.
Meaning that the first component has the largest possible variance, and each succeeding component have lower variance.
In our overview, we are showing the first two PCA components for the tunnel, which are encoded in the coordinates.
As a result, we are able to remove the noise from the data, while making use of fewer quantities.
First component value encodes x coordinate, and second encodes y coordinate (see Figure~\ref{fig:tunnelsPCA}).

Even though we have used PCA for dimension reduction, there are alternative approaches, for example Kernel Principal Component Analysis(KPCA)~\cite{Kim2005KPCA}, Independent Component Analysis (ICA)~\cite{Olshausen1997ICA} or others.
Important property of the approach is the ability to reduce the 10 digits tunnel descriptor to 2D point coordinates and visualize statistical results for the whole matrix.
Visualizing statistical results can help identify clusters and outliers as well as analyze deviation, distribution and correlation.

Natural image statistics were deeply analyzed by Fang et al.~\cite{Fang2013NaturalImageStatistics}, where the authors have designed new visualizations for image statistics.
Our 2D overview is just a simple demonstration, however more complex visualization method can be used, for example Combined design~\cite{Fang2013NaturalImageStatistics} to show the parameters of PCA and Gabor descriptors at the same time.
This is one of the possible future directions of the method.

\subsubsection{Clustering}
Having visual of similarity is a useful tool for the navigation through possible tunnel arrangements.
With points populated 2D space it is easy to see where points are more densely populated (clusters) and which points are more away from others(outliers).
However for successful connection with other views, one needs a proper color depiction of clusters and outliers.
Clustering allows us to make groups of points to determine patterns in the overview.
Clustering has its advantages when the data set is defined and a grouping needs to be determined from it.
Moreover clustering close points to one group in our case means grouping similar tunnels together.
A general open question for clustering is the number of groups usually needs to be know beforehand.
For a user without a knowledge of his data, this might be difficult.
Moreover clustering is a group of different algorithms with the common task.
In general we can say, that there is no objectively "correct" clustering algorithm.
We have experimented with centroid-based clustering, k-means.

The output of the centroid-based clustering is the set of clusters represented by a central vector, which may not necessarily be a member of the data set.
In k-means clustering, the number of clusters is fixed to k, and needs to be specified in advance, which is considered to be one of the main drawback of this algorithm.

K-means is an optimization problem, that reduces distances of the data from the nearest cluster center, which is not a problem in our solution.
In our case, we want to show an unfold representative from each cluster.
As this representation requires available space in window, the number of unfolded tunnels is limited.
We have empirically found out, that showing 5 tunnels at the same time is the limit, which also gives us the limit for k-means clustering.
K-means were chosen for its simplicity, and for its conceptual closeness to nearest neighbor classification.
However, well known problem is with the borders of clusters, because the algorithm is optimizing cluster centers, not cluster borders, and we envision another direction of our future work in experimenting with other families of cluster algorithm such as hierarchical clustering, density clustering and other methods from machine learning.

Important to note is the definition of the distance for clustering algorithm. 
Euclidean distance is easy to imagine and to work with.
However it is hard to see if it is applicable on the points from the image momentum descriptor.
More appropriate might be Mahanalobis distance.
The Mahalanobis distance is a measure of the distance between a point and a distribution.
Mahalanobis distance is unitless and scale-invariant, and takes into account the correlations of the data set.

\begin{figure}[htb]
\includegraphics[width=\linewidth]{img/invariance.png}
\centering
\caption{
Tunnels similarity overview for four different ways of generating image momentum: standard(upper-left), with amino acids coloring permutation(upper-right), rotated(lower-left), and with normalized size of the centerline(lower-right).
Points are colored by the detected clusters.
}
\label{fig:invariance}
\end{figure}

Image momentum descriptor, dimension reduction, and clustering should all bring the same notion of tunnels similarity/dissimilarity.
Image moment might be seen as a problem here, as it fills the data to reduction and clustering.
Original image moment is not invariant to translation, rotation, or scale, but there exist versions which invariant to those properties are.
We have decided to use centralized image momentum, as it is invariant to translation.
All the tunnels have the same rotation, and the same uniform scaling.
Translational invariance helps us with a problem of moved amino-acids, due to change of the centerline length.
As seen in Figure~\ref{fig:invariance}, we have tested the generation of the overview with four different ways of generating the value, which are: standard, tunnels rotated, tunnels scaled, tunnels colored by the different color scheme.
We can see, that eve thou the positional distribution of the points differs, the notion of cluster and two outliers is preserved on all the different ways of generating image moment values.
Moreover the important aspect here is, that for the overview we have a shared space, which allows us to see the neighborhood of the tunnels.
Additionally, the space of the unfolded tunnels is shared as well.
This is due to requirement of employing comparative visualization as a part of the exploration process.

\subsection{Exploration}

\begin{figure}[htb]
\includegraphics[width=\linewidth]{img/app_views.png}
\centering
\caption{
Three basic views.
In the upper part is tunnels unfolding view, for comparative visualization of the tunnels content.
In the bottom is box plot showing the lengths od the tunnels centerline.
In the bottom right is the similarity overview, showing the clusters, and tunnels neighbors.
}
\label{fig:appviews}
\end{figure}

Up until now we have described a way how to build up important parts of our exploration solution.
All of them plays crucial role in the exploration process.
Our exploration solution consists out of couple of views (see Figure~\ref{fig:appviews}).
First, is a view of the set of unfolded tunnels, which allows to make a comparison of spatial and structural aspect of the tunnel.
Second is the scatter plot similarity/dissimilarity overview, which brings forth the notion of the tunnel neighborhood.
And finally is the box plot view, where each tunnel have one box, and where the size of the box corresponds to the size of the tunnel centerline.

With the unfolding tunnels view, user is able to actively compare the shape of the tunnels, where is the bottleneck, and what amino acids are in tunnel.
Unfolded tunnels are positioned side by side, or in other words by juxtaposition composition.
Positioning tunnels from different time frames allows user to see the behavior of the bottleneck as well as the behavior of the amino acids.
Unfolded tunnels needs a space in a view.
Therefore to see the tunnels in this view in full detail is only for limited number of tunnels.
We have empirically found out, that 5 tunnels is the limit for the resolution width 1900.
If more tunnels should be visualized, they need to be additionally downscaled, which means, that with more tunnels, more spatial details are discarded, and unfolded representation gets smaller and smaller.

To show the dataset of hundreds of tunnels from the molecular dynamics simulation, it is unfeasible to use unfolding view as an overview.
Easily shown in an example, with resolution width 1900 and more than 1900 tunnels, we would have more unfolded tunnels than available pixels.
Therefore we have constructed a similarity overview which allows us to code one tunnel as a point.
Having here too many tunnels is still alright, as we are here more interested in tunnels similarity/dissimilarity, shown as a groups and outliers.

One last missing link is to have an ordered overview of the tunnels.
It came naturally to us to show the tunnels as an abstracted box, which height correspond to centerline length.
This way we have a view which allows us to have a unique, and well distinguishable, representation for each tunnel.

Real power of the exploration is on the possibility of brushing between the similarity overview (scatter plot) and tunnels centerline view (box plot). 
Selecting one point in the scatter plot shows which tunnel, at which time, is the corresponding one and shows the unfolded content of the tunnel.
Of course, selection works even in the opposite direction, selecting a box selects a point in a similarity overview.

In overall user have a power to explore the spatial, and content, aspect of the tunnels, by selecting tunnels from the box plot, and scatter plot.
Thanks to first one it is possible to visualize the tunnel development over time, and thanks to latter it is possible to explore the similarity of the tunnel and to see the outliers.

\section{Evaluation}
To demonstrate the usability of our approach we conducted two case studies following the research of our cooperating researchers from the field of protein engineering. 
The first study deals with exploration of simulations of molecular dynamics and the second study focuses on scrutinizing the tunnel shape modified by mutations of a selected tunnel-lining amino acid.

\subsubsection{Exploration of Molecular Dynamics}

\subsubsection{Exploration of Tunnel Mutations}
One of the research topics conducted by the cooperation group of protein engineers is dealing with engineering protein stability and resistance to organic cosolvents~~\cite{Koudelakova2013StabilityAndResistance}.
This is reached by mutating the amino acids around the main tunnel of the DhaA haloalkane dehalogenase protein molecule. 
The paper first presents the confirmation of importance of the amino acids surrounding the tunnel by presenting the results of several mutations of amino acids on different places in the molecule.
It was revealed that by mutating only the amino acids in the close vicinity of the main tunnel the researchers were able to change the stability and resistance of the protein substantially.

\section{Conclusion \& Future work}
We have presented a novel method to explore the shape and the content of the molecular tunnels.
Our approach consists of transforming 3D shape to more readable 2D unfolded representation, using image moment as a descriptor for each tunnel, and providing multiple views on the tunnel data to promote exploration.
The resulting system can interactively show the overall development of the tunnel centerline, the tunnel similarity and dissimilarity, and the shape and content od the selected set of tunnels.

We demonstrated the use cases of the method in two real world examples from the field of biochemistry.
Moreover we have shown, that our method can be used on the temporal data, and on the data with the tunnel mutations.

Our method has several ways of future work, in aspects of the unfolding process, generating tunnels similarity measure, and final visualization of the dataset.
Regarding unfolding we have discussed a possibility to have a more intelligent cutting mechanism. More specifically semantically driven cut, that would follow the borders of the amino acids in tunnel.
For the similarity overview, it is worth wile to try combination of image momentum, reduction, and clustering, that is invariant to amino acids color permutation, rotation, and scale.
Invariant method would allow to compare even between two different setting of two different data sets.
Lastly there are some new ideas of the final visualization composition.
Firstly, to incorporate the unfolded overview for the whole cluster.
We mean here to visualize the clusters side by side, where each cluster would not be seen by one representative, but rather by the variance visualization showing the stability of the cluster.

Going a little bit from the tunnels to the whole molecule, our collaborators have suggested that the whole molecule flattening would be beneficial to visualize and explore in the similar manner.

%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}

%-------------------------------------------------------------------------
\newpage


\end{document}
