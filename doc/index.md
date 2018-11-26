# RootClassification

## Authors
> [**Yifu Wang - 467261**](https://github.com/Luna1996) (Document author)<a id="w"></a>  
> [**Zhuangyu Han - 467528**](https://github.com/BeefZong)<a id="h"></a>

[`W`]:  #w
[`H`]:  #h

> [`W`] and [`H`] indicate the author of the specific part.

## Introduction
> This is the final project for CSE 554A 2018. The goal for this project is to classificate corn roots from 5 data file in cell complex format we learned this term. And we will provide an 3D visiualization tool that user can view the algorithm results and manually correct error if there were any.

## Approch
> * Firstly we want exclude the affect of 'noise', those short root sigment. To do this we will need to assign each edge to a root sigment. Then assign short root sigment to attached root sigment.
> * Second we will determin the morphological upper end of each sigment. And use the posion of this end and the extension cord from this end to classify the roots.
> * Thirdly we will allow human interaction after or before the algorithm started.

##  Implement

> * GUI
>   * 
> * Algorithm
>   * 
> * Tools
>   * [`CCData`](CCData.md/#load-ply-file)