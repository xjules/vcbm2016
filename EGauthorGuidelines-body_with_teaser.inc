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
Later we mention techniques, which have been proposed for 3D data projections and reformation in medical visualization, flow dynamics and other field.

\subsection{Protein Void Detection and Analysis}
\subsection{Projections and Reformation Methods}
\subsection{Comparative Visualization}

\subsection{Flattening techniques}
\subsection{Comparative Visualization}
\section{Method}
\subsection{Flattening}
\subsection{Comparative Visualization}
\subsection{Image Moment}
\subsubsection{Clustering}
\subsubsection{Composition}
\section{Evaluation}
\section{Discussion}
\section{Conclusion \& Future work}


Image moments~\cite{flusser09moments} provide a practical and useful way to describe image objects. In our case, images containing flattened tunnels are further characterized by 10 different image moments to condense the information.
%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}

%-------------------------------------------------------------------------
\newpage


\end{document}
