#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>       /* time */
#include "matx.h"
#include "neu.h"

using namespace std;

int main(int, char **argv)
{
   matrix *tmp;
   matrix *inLearning, *outLearning, *inTst, *outTst;

   loadMattxt("data.data", &tmp);

   initmat(&inLearning, (tmp->rows * 2 / 3), tmp->cols - 1, 0.0);
   initmat(&inTst, (tmp->rows / 3), tmp->cols - 1, 0.0);
   initmat(&outLearning, (tmp->rows * 2 / 3), 9, 0.0);
   initmat(&outTst, (tmp->rows / 3), 9, 0.0);

   int l = 0;
   for (int i = 0; i < (tmp->rows - 1); i = i + 3)
   {
      for (int j = 1; j < tmp->cols; j++)
      {
         elm(inLearning, l, j - 1)     = elm(tmp, i, j);
         elm(inLearning, l + 1, j - 1) = elm(tmp, i + 1, j);
         elm(inTst, i / 3, j - 1)      = elm(tmp, i + 2, j);
      }
      switch ((int)elm(tmp, i, 0))
      {
      case 1:
         elm(outLearning, l, 0) = 1;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 2:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 1;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 3:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 1;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 4:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 1;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 5:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 1;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 6:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 1;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 7:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 1;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 0;
         break;

      case 8:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 1;
         elm(outLearning, l, 8) = 0;
         break;

      case 9:
         elm(outLearning, l, 0) = 0;
         elm(outLearning, l, 1) = 0;
         elm(outLearning, l, 2) = 0;
         elm(outLearning, l, 3) = 0;
         elm(outLearning, l, 4) = 0;
         elm(outLearning, l, 5) = 0;
         elm(outLearning, l, 6) = 0;
         elm(outLearning, l, 7) = 0;
         elm(outLearning, l, 8) = 1;
         break;

      default:
         ;
      }
      if ((l + 1) < tmp->rows)
      {
         switch ((int)elm(tmp, i + 1, 0))
         {
         case 1:
            elm(outLearning, l + 1, 0) = 1;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 2:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 1;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 3:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 1;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 4:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 1;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 5:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 1;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 6:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 1;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 7:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 1;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 8:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 1;
            elm(outLearning, l + 1, 8) = 0;
            break;

         case 9:
            elm(outLearning, l + 1, 0) = 0;
            elm(outLearning, l + 1, 1) = 0;
            elm(outLearning, l + 1, 2) = 0;
            elm(outLearning, l + 1, 3) = 0;
            elm(outLearning, l + 1, 4) = 0;
            elm(outLearning, l + 1, 5) = 0;
            elm(outLearning, l + 1, 6) = 0;
            elm(outLearning, l + 1, 7) = 0;
            elm(outLearning, l + 1, 8) = 1;
            break;

         default:
            ;
         }
      }
      if ((i + 2) < tmp->rows)
      {
         switch ((int)elm(tmp, i + 2, 0))
         {
         case 1:
            elm(outTst, i / 3, 0) = 1;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 2:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 1;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 3:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 1;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 4:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 1;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 5:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 1;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 6:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 1;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 7:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 1;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 8:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 1;
            elm(outTst, i / 3, 8) = 0;
            break;

         case 9:
            elm(outTst, i / 3, 0) = 0;
            elm(outTst, i / 3, 1) = 0;
            elm(outTst, i / 3, 2) = 0;
            elm(outTst, i / 3, 3) = 0;
            elm(outTst, i / 3, 4) = 0;
            elm(outTst, i / 3, 5) = 0;
            elm(outTst, i / 3, 6) = 0;
            elm(outTst, i / 3, 7) = 0;
            elm(outTst, i / 3, 8) = 1;
            break;

         default:
            ;
         }
      }
      l = l + 2;
   }

   matrix *inLearningNorm, *inTstNorm, *uext;

   initmat(&inLearningNorm, inLearning->rows, inLearning->cols, 0.0);
   initmat(&inTstNorm, inTst->rows, inTst->cols, 0.0);
   initmat(&uext, inLearning->cols, 2, 0.0);

   matnormp(inLearning, &inLearningNorm, &uext, 1);
   matnormpext(inTst, &inTstNorm, uext, 1);

   saveMatD("uext", uext);


   matrix *nninput, *nnoutput;
   initmat(&nninput, inTst->cols, 1, 0.0);
   initmat(&nnoutput, outTst->cols, 1, 0.0);

   int antin     = inLearning->cols;
   int antN      = 10;
   int antout    = outLearning->cols;
   int antEpokes = 2000;

   matrix *perf, *perfTst;
   initmat(&perf, antEpokes + 1, antout, 0.0);
   initmat(&perfTst, antEpokes + 1, antout, 0.0);


   mlp_net *nn_net;
   srand(time(NULL));
   mlp_gaussinit(&nn_net, antin, antN, antout, 0.0, .4);

   CalcPerf(nn_net, &perf, inLearningNorm, outLearning, 0);
   CalcPerf(nn_net, &perfTst, inTstNorm, outTst, 0);


   for (int l = 0; l < antEpokes; l++)
   {
      mlp_train(nn_net, inLearningNorm, outLearning, 20, 0.02);

      srand(time(NULL));
      ShuffleMat(inLearningNorm, outLearning, tmp);

      CalcPerf(nn_net, &perf, inLearningNorm, outLearning, l + 1);
      CalcPerf(nn_net, &perfTst, inTstNorm, outTst, l + 1);
   }

   save_bpenet("DataNet.nn", nn_net);
   saveMattxt("perf.txt", perf);
   saveMattxt("perfTst.txt", perfTst);



   int NoErr = 0;
   for (int j = 0; j < inTst->rows; j++)
   {
      for (int k = 0; k < inTst->cols; k++)
      {
         elm(nninput, k, 0) = elm(inTstNorm, j, k);
      }

      bpe_forward(nninput, nn_net, &nnoutput);

      printf("Net out: \t\t%6.2f\t\t%6.2f \t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\n", elm(nnoutput, 0, 0), elm(nnoutput, 1, 0), elm(nnoutput, 2, 0), elm(nnoutput, 3, 0), elm(nnoutput, 4, 0), elm(nnoutput, 5, 0), elm(nnoutput, 6, 0), elm(nnoutput, 7, 0), elm(nnoutput, 8, 0));
      printf("Desired: \t\t%6.2f\t\t%6.2f \t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\t\t%6.2f\n\n", elm(outTst, j, 0), elm(outTst, j, 1), elm(outTst, j, 2), elm(outTst, j, 3), elm(outTst, j, 4), elm(outTst, j, 5), elm(outTst, j, 6), elm(outTst, j, 7), elm(outTst, j, 8));

      if (((elm(outTst, j, 0) == 1) && (elm(nnoutput, 0, 0) < 0.5)) ||
          ((elm(outTst, j, 1) == 1) && (elm(nnoutput, 1, 0) < 0.5)) ||
          ((elm(outTst, j, 2) == 1) && (elm(nnoutput, 2, 0) < 0.5)) ||
          ((elm(outTst, j, 3) == 1) && (elm(nnoutput, 3, 0) < 0.5)) ||
          ((elm(outTst, j, 4) == 1) && (elm(nnoutput, 4, 0) < 0.5)) ||
          ((elm(outTst, j, 5) == 1) && (elm(nnoutput, 5, 0) < 0.5)) ||
          ((elm(outTst, j, 6) == 1) && (elm(nnoutput, 6, 0) < 0.5)) ||
          ((elm(outTst, j, 7) == 1) && (elm(nnoutput, 7, 0) < 0.5)) ||
          ((elm(outTst, j, 8) == 1) && (elm(nnoutput, 8, 0) < 0.5)))
      {
         NoErr++;
      }
   }
   printf("No. of errors: %d\n", NoErr);
   write_bpenet(nn_net);
   return(0);
}
