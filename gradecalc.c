#include <stdio.h>

#define prereqWeight 0.1
#define projectWeight 0.3
#define mid1Weight 0.2
#define mid2Weight 0.2
#define FinalWeight 0.2

double gradeNeeded(double desiredPercentage, double currentGrade);

int main()
{
 double prereq, zero, one, two, three, midterm1, midterm2, final;
 prereq = zero = one = two = three = midterm1 = midterm2 = final = 0.0;

 printf("Please enter prereq grade: ");
 scanf("%lf", &prereq);
 printf("Please enter zero grade: ");
 scanf("%lf", &zero);
 printf("Please enter one grade: ");
 scanf("%lf", &one);
 printf("Please enter two grade: ");
 scanf("%lf", &two);
 printf("Please enter three grade: ");
 scanf("%lf", &three);
 printf("Please enter midterm1 grade: ");
 scanf("%lf", &midterm1);
 printf("Please enter midterm2 grade: ");
 scanf("%lf", &midterm2);

 prereq /= 100.0;
 midterm1 /= 100.0;
 midterm2 /= 100.0;
 double projectGrade = (zero + one + two + three) / 400.0;
 double currentGrade = (prereqWeight * prereq) + 
                        (mid1Weight * midterm1) + 
                       (mid2Weight * midterm2) + 
                       (projectWeight * projectGrade);

 printf("\n\nFor an A+, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.98, currentGrade));
 printf("For an A, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.93, currentGrade));
 printf("For an A-, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.90, currentGrade));
 printf("For a B+, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.88, currentGrade));
 printf("For a B, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.83, currentGrade));
 printf("For a B-, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.80, currentGrade));
 printf("For a C+, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.78, currentGrade));
 printf("For a C, you will need to make %.2lf%% on the final.\n",
   gradeNeeded(0.73, currentGrade));
 printf("For a C-, you will need to make %.2lf%% on the final.\n\n",
   gradeNeeded(0.70, currentGrade));

 return 0;
}
double gradeNeeded(double desiredPercentage, double currentGrade)
{
 return ((desiredPercentage - currentGrade ) / FinalWeight) * 100;
}