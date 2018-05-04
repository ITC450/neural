#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>       /* time */
#include "matx.h"
#include "neu.h"

int main( int, char** argv )
{

    matrix *tmp;
    matrix *inLearning, *outLearning, *inTst, *outTst;

    loadMattxt("wine.data",&tmp);

    initmat(&inLearning,    (tmp->rows*2/3), tmp->cols-1, 0.0);
    initmat(&inTst,         (tmp->rows/3),   tmp->cols-1, 0.0);
    initmat(&outLearning,   (tmp->rows*2/3),  3, 0.0);
    initmat(&outTst,        (tmp->rows/3),    3, 0.0);

    int l=0;
    for(int i=0; i<(tmp->rows-1); i=i+3)
    {
        for (int j=1; j< tmp->cols; j++)
        {
            elm(inLearning, l,   j-1)= elm(tmp, i,   j);
            elm(inLearning, l+1, j-1)= elm(tmp, i+1, j);
            elm(inTst,      i/3, j-1)= elm(tmp, i+2, j);
        }
        switch ((int)elm(tmp,i,0))
        {
        case 1 :
            elm(outLearning,l,0) =1;
            elm(outLearning,l,1) =0;
            elm(outLearning,l,2) =0;
            break;
        case 2 :
            elm(outLearning,l,0) =0;
            elm(outLearning,l,1) =1;
            elm(outLearning,l,2) =0;
            break;
        case 3 :
            elm(outLearning,l,0) =0;
            elm(outLearning,l,1) =0;
            elm(outLearning,l,2) =1;
            break;
        default :
            ;
        }
        if ((l+1) < tmp->rows)
        {
            switch ((int)elm(tmp,i+1,0))
            {
            case 1 :
                elm(outLearning,l+1,0) =1;
                elm(outLearning,l+1,1) =0;
                elm(outLearning,l+1,2) =0;
                break;
            case 2 :
                elm(outLearning,l+1,0) =0;
                elm(outLearning,l+1,1) =1;
                elm(outLearning,l+1,2) =0;
                break;
            case 3 :
                elm(outLearning,l+1,0) =0;
                elm(outLearning,l+1,1) =0;
                elm(outLearning,l+1,2) =1;
                break;
            default :
                ;
            }
        }
        if ((i+2) < tmp->rows)
        {
            switch ((int)elm(tmp,i+2,0))
            {
            case 1 :
                elm(outTst,i/3,0) =1;
                elm(outTst,i/3,1) =0;
                elm(outTst,i/3,2) =0;
                break;
            case 2 :
                elm(outTst,i/3,0) =0;
                elm(outTst,i/3,1) =1;
                elm(outTst,i/3,2) =0;
                break;
            case 3 :
                elm(outTst,i/3,0) =0;
                elm(outTst,i/3,1) =0;
                elm(outTst,i/3,2) =1;
                break;
            default :
                ;
            }
        }
        l=l+2;
    }

    matrix *inLearningNorm, *inTstNorm, *uext;

    initmat(&inLearningNorm, inLearning->rows,   inLearning->cols,  0.0);
    initmat(&inTstNorm,      inTst->rows,        inTst->cols,       0.0);
    initmat(&uext,           inLearning->cols,   2,                 0.0);

    matnormp(inLearning, &inLearningNorm, &uext, 1);
    matnormpext(inTst,   &inTstNorm,      uext,  1);

    saveMatD("uext", uext);

    srand (time(NULL));
    ShuffleMat(inLearningNorm, outLearning, tmp);

    matrix *nninput, *nnoutput;
    initmat(&nninput,  inTst->cols,  1, 0.0);
    initmat(&nnoutput, outTst->cols, 1, 0.0);

    sph_net *nn_net;

    Sphere_init(&nn_net, 5.0);
    Sphere_train(nn_net, inLearningNorm, outLearning);

    save_sphnet("sphnet.nn", nn_net);



    int conf, antC;
    int NoErr=0;
    for (int j = 0; j < inTst->rows; j++)
    {
        for (int k = 0; k < inTst->cols; k++)
            elm(nninput, k, 0) = elm(inTstNorm, j, k);

        Sphere_run(nn_net, nninput, &nnoutput, &conf, &antC);

        printf("Desired: \t\t%6.2f\t\t%6.2f \t\t%6.2f\n",elm(outTst,j,0), elm(outTst,j,1), elm(outTst,j,2));
        printf("NN out: \t\t%6.2f\t\t%6.2f \t\t%6.2f\n\n",elm(nnoutput,0,0), elm(nnoutput,1,0), elm(nnoutput,2,0));

        if (((elm(outTst,j,0)==1)&&(elm(nnoutput,0,0) <0.5)) ||
                ((elm(outTst,j,1)==1)&&(elm(nnoutput,1,0) <0.5)) ||
                ((elm(outTst,j,2)==1)&&(elm(nnoutput,2,0) <0.5)))
        {
            NoErr++;
        }

    }
    printf("No. of errors: %d\n",NoErr);
    write_sphnet(nn_net);
    return 0;
}
