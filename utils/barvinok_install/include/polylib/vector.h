/*
    This file is part of PolyLib.

    PolyLib is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PolyLib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PolyLib.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _vector_H_ 
#define _vector_H_

#if defined(__cplusplus)
extern "C" {
#endif

int ConstraintSimplify(Value_poly *old, Value_poly *n, int len, Value_poly* v);
Value_poly* value_alloc(int want, int *got);
void value_free(Value_poly *p, int size);

extern void Factorial(int n,Value_poly *result);
extern void Binomial(int n,int p,Value_poly *result);
extern void CNP(int a,int b,Value_poly *result);
extern void Gcd(Value_poly a,Value_poly b,Value_poly *result);
extern int First_Non_Zero(Value_poly *p, unsigned length);
extern Vector *Vector_Alloc(unsigned length);
extern void Vector_Free(Vector *vector);
extern void  Vector_Print(FILE *Dst, const char *Format, Vector *Vec);
extern Vector *Vector_Read(void);
extern void Vector_Set(Value_poly *p,int n,unsigned length);
extern void Vector_Exchange(Value_poly *p1, Value_poly *p2, unsigned length);
extern void Vector_Copy(Value_poly *p1, Value_poly *p2, unsigned length);
extern void Vector_Add(Value_poly *p1,Value_poly *p2,Value_poly *p3,unsigned length);
extern void Vector_Sub(Value_poly *p1,Value_poly *p2,Value_poly *p3,unsigned length);
extern void Vector_Or(Value_poly *p1,Value_poly *p2,Value_poly *p3,unsigned length);
extern void Vector_Scale(Value_poly *p1, Value_poly *p2, Value_poly lambda, unsigned
			 length);
extern void Vector_AntiScale(Value_poly *p1,Value_poly *p2,Value_poly lambda,
			                unsigned length);
extern void Vector_Oppose(Value_poly *p1, Value_poly *p2, unsigned length);
extern void Inner_Product(Value_poly *p1,Value_poly *p2,unsigned length, Value_poly *result);
extern void Vector_Max(Value_poly *p,unsigned length, Value_poly *result);
extern void Vector_Min(Value_poly *p,unsigned length, Value_poly *result);
extern void Vector_Combine(Value_poly *p1,Value_poly *p2,Value_poly *p3,Value_poly
                            lambda, Value_poly mu, unsigned length);
extern int  Vector_Equal(Value_poly *Vec1,Value_poly *Vec2,unsigned n);
extern void Vector_Min_Not_Zero(Value_poly *p,unsigned length,int *index,Value_poly
                     *result);
extern void Vector_Gcd(Value_poly *p,unsigned length,Value_poly *result);
extern void Vector_Map(Value_poly *p1,Value_poly *p2,Value_poly *p3,unsigned
		       length, Value_poly *(*f)(Value_poly,Value_poly));
extern void Vector_Normalize(Value_poly *p,unsigned length);
extern void Vector_Normalize_Positive(Value_poly *p,int length,
				      int pos);
extern void Vector_Reduce(Value_poly *p,unsigned length,
                  void(*f)(Value_poly,Value_poly *),Value_poly *result);
extern void Vector_Sort(Value_poly *vector,unsigned n);
extern int Vector_IsZero(Value_poly * v, unsigned length);

#if defined(__cplusplus)
}
#endif

#endif /* _vector_H_ */
