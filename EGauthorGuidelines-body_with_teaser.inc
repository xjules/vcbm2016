% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[Unrolling and Interactive Exploration of Protein Tunnels and their Dynamics]%
      {Unrolling and Interactive Exploration of Protein Tunnels and their Dynamics}

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
  \caption{TODO change image}
\label{fig:teaser}
}

\maketitle

\begin{abstract}
   TODO
   (see http://www.acm.org/class/1998/).

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
Therefore, by exploring the amount and properties of void space inside molecules, we are able to assess the possibility of a ligand with specific properties to enter these molecules.
The void space can be categorized according to different criteria, the most common approach takes into account the accessibility of the void space form the molecular surface.
Then we can distinguish between inner closed cavities and paths.
The closed cavities are inaccessible from the surface and are buried in the molecular structure.
The accessible paths can be further divided to those which connect a specific site (so called active site) inside the molecule with its surface and those traversing the whole molecule.
The first type of paths is denoted as tunnels and the second as channels or pores.
In our research we are interested mainly in tunnels in protein molecules because they enable to transport small ligands to the protein active site where a mutual chemical reaction can occur. 
This process is crucial namely in drug design and protein engineering.
From the latter field also comes our conducted user study which we present at the end of the paper.
In our research we are focusing namely on protein structures, however, the proposed method is applicable to any kind of molecule containing tunnels.


Molecular dynamics (cite dynasome)

\section{Related Work}

The approach proposed in this paper was designed for comparison and visual exploration of multiple protein tunnels.
The majority of existing representations aim to visualize the 3D overview of the protein tunnel shape. 
Such realistic spatial representations, however, fail exactly in cases when it is required to compare large number of protein tunnels or evaluate the development of single tunnel over longer period of time.
The problem is that these methods do not provide fast and intuitive way to explore the protein tunnels and their surrounding mainly due to the occlusion (see Figure~\ref{fig:tunnel_with_aa}).

\begin{figure}[htb]
 \includegraphics[width=\linewidth]{img/tunnel_with_aa.png}
 \centering
  \caption{{\color{red}TODO: change image, \ie use real surface representation}}
\label{fig:tunnel_with_aa}
\end{figure}

This problem was already partially addressed in other domains, for instance, in the filed of medical visualization.
Here the methods based on 3D data projections and reformations are frequently used in order to reveal various anatomical {\color{red}features}.
Nevertheless, due to the nature of the data, these methods mostly focus on the exploration rather then comparison.
On the other hand, the comparative visualization in connection with surface reformation was applied many times when studding the flow dynamics.

Unfortunately, the proper visualization of surface itself is not enough when comparing the protein tunnels. 
Even though the tunnel shape is important~{\color{red}{\cite{XYZ}}}, the essential information here is the conformation of surrounding amino acids and their biochemical properties~{\color{red}{\cite{XYZ}}}. 
Therefore, the biochemist tend to use highly abstract representations for protein tunnel comparison even if these methods do not provide any information about the tunnel shape {\color{red}whatsoever}.

This paper is describing a new design which is connecting space reformation with abstract amino acid representation in order to fill the mentioned gap in the area of biology visualization.
Hence, in the following sections we touch upon all the aforementioned related work in more details. 
Firstly we provide the reader with overview of the related work regarding the protein void detection and their visualization. 
Later we mention techniques, which have been proposed for 3D data projections and reformation in medical visualization, flow dynamics and other fields.

\subsection{Protein Void Detection and Analysis}
The early approaches for protein tunnel detection were grid-based~\cite{Petrek2006Caver, Ho2008Hollow, Voss20103V}. 
For instance, in the first mentioned paper~\cite{Petrek2006Caver} authors proposed to enclose the protein into a uniform grid.
The value of the each voxel is computed based on the amount of surrounding empty space.
The Dijkstra algorithm in used afterwards in order to find the set of widest empty paths (tunnels) leading from the active site to the protein surface.

Even thought these techniques allow to describe void of nearly any shape, the precision and performance of the grid-based methods highly depends on the grid resolution. 
These drawbacks were later overcome by Voronoi diagram-based methods \cite{Medek2007Voronoi, Petrek2007MOLE, Yaffe2008MolAxis, Lindow2011Voronoi, Chovancova2012Caver3}.
These methods are similar to the previous approach but they first compute a Voronoi diagram of the protein and use Dijkstra algorithm on top it. 

Such approach enables to save a huge amount of resources, however, the resulting tunnel is usually represented by a set of spheres following the set of Voronoi edges. 
However, the cross-sections of the protein tunnels are rather non-circular and hence the sphere representation may lead to misinterpretation of the analyzed tunnel.
Therefore recently some alternative methods combining the two aforementioned techniques appeared~\cite{Jurcik2015Visibility}.

Nowadays, the biochemists are more and more focusing on the analysis of simulations of molecular dynamics rather than on static molecules, as
these techniques yield more biochemically relevant results.
In order to analyze tunnels inside such dynamic environment it is necessary to correctly register and follow them over time. 
There are tools capable of such clustering, for instance, MOLE~2.0~\cite{Sehnal2013Mole2} or CAVER~3.0~\cite{Chovancova2012Caver3}. Additionally, other methods such as~\cite{Parulek2013CavityAnalysis,Lindow2013DynamicCavities, Jurcik2016TransparentMolecularSurface} were presented in order to enable extractions of dynamic cavities in real-time.

Finally, as already mentioned for the analysis of the protein tunnels the physio-chemical properties of amino acids in the vicinity of the tunnel are equally important as geometrical aspects. 
There are several methods focusing on the evaluation of the protein tunnel surroundings over time~\cite{Byska2015MoleCollar, Byska2015AnimoAminoMiner}.
The disadvantage of these solutions is that they mostly omit the mutual spatial orientation of the extracted amino acids in order to reasonable visualize the huge amount of data over time.


\subsection{Projections and Reformation Methods}
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

\subsection{Image Moment}
Image moments~\cite{Flusser09Moments} provide a practical and useful way to describe image objects. Each image $I(x,y)$ is described by the set of moments
\begin{equation}
M_{ij} = \sum_{x}\sum_{y}x^iy^j I(x,y)
\end{equation} 
In our case, images containing flattened tunnels are further characterized by 10 different image centralized moments to condense the information.
\begin{equation}
\mu_{pq} = \sum_{m}^{p}\sum_{n}^{q}{p \choose m}{q \choose n}\left(-{M_{10} \over M_{00}}\right)^{(p-m)}\left(-{M_{01} \over M_{00}}\right)^{(q-n)}
\end{equation} 

\subsection{PCA}
\subsubsection{Clustering}
\subsubsection{Exploration}
\section{Evaluation}
\section{Discussion}
\section{Conclusion \& Future work}

%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}

%-------------------------------------------------------------------------
\newpage


\end{document}
