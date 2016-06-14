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
{\color{red}Additionally, other methods such as~\cite{Parulek2013CavityAnalysis,Lindow2013DynamicCavities, Jurcik2016TransparentMolecularSurface} were presented in order to enable extractions of dynamic cavities in real-time.}

Finally, as already mentioned for the analysis of the protein tunnels the physico-chemical properties of amino acids in the vicinity of the tunnel are equally important as its geometrical aspects. 
There are several methods focusing on the evaluation of the protein tunnel surroundings over time~\cite{Byska2015MoleCollar, Byska2015AnimoAminoMiner}.
{\color{red}The disadvantage of these solutions is that they mostly omit the mutual spatial orientation of the extracted amino acids in order to visualize huge amount of data over time.}


\subsection{Projections and Reformation Methods}
The core idea of our technique for comparative visualization of protein tunnels is based on unfolding 3D tunnel surface in to 2D in order to prevent occlusion problems.
The similar approach is commonly used in other domains as well.

For example Kretschmer et al.\cite{Kretschmer2014AnatomyDriveReformation} presented method for reformation of volumetric data driven by particular geometry -- in this case an anatomy of a specific patient.
This method is an extenstion of the previous work of Liu et al.~\cite{Liu2008LocalGlobalMeshParametrization} for volumetric data. 
Unfortunately, since both methods are relatively general, they also produce an inevitable distortion in the distance. 
This is unsatisfactory when comparing protein tunnels since here the main focus is placed on tunnel length, bottleneck \todo{define bottleneck? or it has be done in intro?}whereabouts, and overall surface shape.

In order to minimize the distortion as much as possible we can exploit the unique tubular shape of protein tunnels.
The similar approach was used, for instace, by Gurijala et al.~\cite{Gurijala2013Colon}.
They presented a method that produces a rectangular flattening of the colon model.
This method handles very well a topological noise and preserves the colon wall shape, which allows to easily observe the polyps (abnormal growth of tissue) inside the colon. 
The proposed normalized rectangle view, however, does not depict the radius of colon.
Although, this can be omit in this particular use case, it is essential when designing a comparative visualization of protein tunnels.

Another example of surface reformation of the tubular structures is vessel visualization.
The Curved Planar Reformation (CPR)~\cite{Kanitsar2002CPR} is wide know technique commonly used for diagnosis vascular diseases of peripheral arteries with single dominant direction.
In order to investigate the vessels with arbitrary orientation, Mistelbauer et al.~\cite{Mistelbauer2012CP} proposed Centerline Reformations (CR).
The CR is an extension of CPR method but it uses a wavefront propagation of vessel centerline for automatic setting of the vector of interest.
{\color{red} Nevertheless, there is a trade-off between the visibility
of the vessels and the displayed size of the surrounding tissue.} \todo{copy-pasted + is it really drawback in comparison to our approach?}
In order solve this, another variant of the CPR method was proposed by Auzinger et al.~\cite{Auzinger2013Vessel}. 
This method avoids the visibility issues of CPR and CR caused by the projection by computing the vessel lumen (empty space inside of a vessel) fully in 3D. 
This is done by finding a cut through the vessel and surrounding tissue orthogonal to vessel centerline and view direction.
The view-dependency would, however, cause some issues in our case, since we are aiming for comparative visualization and hence we need to find the same cut for each tunnel in order to obtain a common space.
Moreover, the proposed cutaway discards part of the vessel surface while we want to communicate the shape and biochemical properties of the whole protein tunnel.

{\color{red}When speaking about vessels it is only natural to mention also a related work regarding the comparative visualization used when exploring the flow dynamics....TBA}\todo{toto asi neni nejlepsi formulace} 
  

\subsection{Comparative Visualization}

\subsection{Flattening techniques}
\subsection{Comparative Visualization}
\section{Flattening Based Exploration}
\begin{figure*}[htb]
\includegraphics[width=0.8\linewidth]{img/processing_pipeline.jpg}
\centering
\caption{{\color{red}TODO: change image}}
\label{fig:processing_pipeline}
\end{figure*}
Main focus of our work is to allow exploration of molecular tunnels in molecular dynamics simulation.
In there tunnel develops over time and changes its shape.
Raw data from such a simulation is the set of 3D objects representing the tunnel shape over time.
There is no trivial direct way of how to orient/position 3D representation of the tunnels for exploration of its similarities and dissimilarities.
Main problems are the self-occlusion of tunnel features in 3D, and occlusion between multiple tunnels.
Moreover there is always a limit of how many 3D objects users can explore at the same time in one window.
To overcome the problem of tunnel self-occlusion we are transforming a 3D object to 2D representation by flattening.
Moreover the spatially reduced flattened tunnels speeds up the exploration of the similarities, or dissimilarities.
However molecular dynamics consists of thousands time steps.
Comparative visualization of the shape of all the tunnels, flattened or not, is therefore challenging.
As a descriptor for the tunnel we are employing image momentum for the unfolded tunnels.
Image momentum is well known descriptor for image analysis and classification.
To bring the tunnels closer to user, we have employed a PCA for dimension reduction.
With PCA we can show the tunnels similarities/dissimilarities as a distance between two points in 2D domain.
Having multiple view, with interaction allows to explore the space of tunnels in 2D as a scatter-plot and at the same time to compare spatial characteristics of the unfolded tunnels.
\subsection{Flattening}
For each tunnel we have its shape as a triangle mesh, centerline as a graph of connected points, and information about tunnel hydrophobicity, charge, and hydrogen bond stored for each vertex of the triangle mesh.
Moreover, we have a set of characteristics, that are of utmost importance to explore.
In our case we want to clearly communicate three features.
Going from the most to the least important.
First one is the positioning, and distribution of amino acids, which creates the tunnel.
Second is the spatial information of the tunnel length, and its thickness development.
Third feature is the notion of shape. 
Meaning that user should be able to detect {\color{red}{"bulky"}} areas.

\begin{figure}[htb]
\includegraphics[width=\linewidth]{img/unfolding_in_out.jpg}
\centering
\caption{{\color{red}TODO: change image}}
\label{fig:processing_pipeline}
\end{figure}

The general idea of our flattening method is the parametrization.
Given the centerline curve $\mathbf{c}(t) : [t_0, t_1]$ of the tunnel, and the cut direction $\mathbf{v}$ the surface $M$ is given by
\begin{equation}
M(t, a) = \mathbf{c}(t) + s\mathbf{v}\times\mathbf{c}(t) \quad t \in [t_0, t_1], \quad a \in [0, 360]
\end{equation}
In other words, our method is based on the slicing of the tunnel by the plane perpendicular to centerline tangent at position $\mathbf{c}(t)$, and sampling the slice by the rays coming from the $\mathbf{c}(t)$ with the direction of the rotated cutting vector $\mathbf{v}$ around the centerline tangent by angle $s$.

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
A(t, a_j) = (t, \sum_{l=0}^{j} D(a_l, a_{l+1}))
\end{equation} 

With our unfolding method we have in 2D encoded values from the tunnel surface.
Moreover, the size of the tunnel over the centerline is accurately preserved, as well as the size of the amino acids from the surface and their respective neighborhood.

Connecting the same angle samples together we get a shape description, which communicates the changes of the tunnel shape, for example at the place where the lines are dense the tunnel is thinner.
On the other hand more scattered lines says, that the tunnel is broader.

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
First component value encodes x coordinate, and second encodes y coordinate (see Figure~\ref{fig:tunnelsPCA}).

a little bit more

Other dimension reduction things

Clustering

K-means

Other clustering things

Invariance of the method
\subsubsection{Exploration}
\section{Evaluation}
To demonstrate the usability of our approach we conducted two case studies following the research of our cooperating researchers from the field of protein engineering. 
The first study deals with exploration of simulations of molecular dynamics and the second study focuses on scrutinizing the tunnel shape modified by mutations of a selected tunnel-lining amino acid.

\subsubsection{Exploration of Molecular Dynamics}

\subsubsection{Exploration of Tunnel Mutations}
One of the research topics conducted by the cooperation group of protein engineers is dealing with engineering protein stability and resistance to organic cosolvents~~\cite{Koudelakova2013StabilityAndResistance}.
This is reached by mutating the amino acids around the main tunnel of the DhaA haloalkane dehalogenase protein molecule. 
The paper first presents the confirmation of importance of the amino acids surrounding the tunnel by presenting the results of several mutations of amino acids on different places in the molecule.
It was revealed that by mutating only the amino acids in the close vicinity of the main tunnel the researchers were able to change the stability and resistance of the protein substantially.


\section{Discussion}
\section{Conclusion \& Future work}

%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}

%-------------------------------------------------------------------------
\newpage


\end{document}
