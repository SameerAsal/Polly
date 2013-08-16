; ModuleID = 'mem-bw-test.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@B = common global [200 x i32] zeroinitializer, align 16
@A = common global [200 x [200 x i32]] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  br label %for.cond1.preheader

for.cond1.preheader:                              ; preds = %entry.split, %for.inc8
  %indvar13 = phi i64 [ 0, %entry.split ], [ %indvar.next14, %for.inc8 ]
  %arrayidx = getelementptr [200 x i32]* @B, i64 0, i64 %indvar13
  br label %for.body3

for.body3:                                        ; preds = %for.cond1.preheader, %for.body3
  %indvar = phi i64 [ 0, %for.cond1.preheader ], [ %indvar.next, %for.body3 ]
  %arrayidx7 = getelementptr [200 x [200 x i32]]* @A, i64 0, i64 %indvar13, i64 %indvar
  %0 = load i32* %arrayidx, align 4
  %mul = mul nsw i32 %0, 90
  store i32 %mul, i32* %arrayidx7, align 4
  %indvar.next = add i64 %indvar, 1
  %exitcond = icmp ne i64 %indvar.next, 200
  br i1 %exitcond, label %for.body3, label %for.inc8

for.inc8:                                         ; preds = %for.body3
  %indvar.next14 = add i64 %indvar13, 1
  %exitcond15 = icmp ne i64 %indvar.next14, 200
  br i1 %exitcond15, label %for.cond1.preheader, label %for.end10

for.end10:                                        ; preds = %for.inc8
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf"="true" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "unsafe-fp-math"="false" "use-soft-float"="false" }
