
这里提供美图秀秀非常早先的一个版本(相关资源文章最后给出)，我们使用AndroidKiller反编译该apk，
然后获取到美图秀秀的源代码以及so库文件，然后尝试在自己的程序中调用美图秀秀的so库文件，
实现美图秀秀美化图片的功能。

一、查看美图秀秀的美图效果

首先看一下美图秀秀处理图片的流程和效果，apk安装完毕，可以看到软件logo

![](pic/01.jpg)

接着打开软件，进入美图秀秀首页

![](pic/02.png)

点击美化图片按钮，进入图片选择页面

![](pic/03.png)


接着点击“从相册选择”按钮，然后选取一张图片

![](pic/原图.jpg)

然后选择图片特效，右侧滑动选择“经典HDR”效果，就可以看到图片效果了

![](pic/04.png)

二、反编译apk获取源代码和so库文件

我们使用反编译软件AndroidKiller对该apk进行反编译，具体下载和反编译请自行百度，很简单，这里就不讲述了

可以看到整个apk项目的整体结构：

![](pic/项目结构图.png)


三、我们在项目中使用美图秀秀的so库文件，实现图片处理的功能

![](pic/so文件.png)

1、复制armeabi文件夹以及so库文件到我们项目的libs目录下面，然后依然要在gradle中设置：

```
    sourceSets {
        main {
            jniLibs.srcDirs = ['libs']
        }
    }
```

2、我们知道的.so库文件中的Java对象中的native方法都是有完整的包名映射路径的，所以我们需要查看美图秀秀中的
native方法都放在哪里，经过分析（具体分析过程放在第四步中），我们可以发现全部都集中在一个名字叫做JNI的对象中：

```java
package com.mt.mtxx.image;

public class JNI {
    public native void AutoColor(byte[] paramArrayOfByte, int paramInt1, int paramInt2, int paramInt3, int paramInt4);

    public native void AutoColorLevel(byte[] paramArrayOfByte, int paramInt1, int paramInt2, boolean paramBoolean);

    public native void AutoConstrast(byte[] paramArrayOfByte, int paramInt1, int paramInt2);

    public native void AutoWhiteBalance(byte[] paramArrayOfByte, int paramInt1, int paramInt2);

    public native void BackWeak(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, int paramInt1, int paramInt2, int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt3, byte[] paramArrayOfByte3, int paramInt4, int paramInt5);

    public native void BackWeak2(byte[] paramArrayOfByte1, int paramInt1, int paramInt2, int paramInt3, int paramInt4, byte[] paramArrayOfByte2, int paramInt5, int paramInt6);

    public native void BackWeakLine(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, int[] paramArrayOfInt3, int[] paramArrayOfInt4, float paramFloat, int paramInt3, int paramInt4);

    public native void BackWeakOne(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, int paramInt3, int paramInt4, byte[] paramArrayOfByte, int paramInt5, int paramInt6);

    public native void CColorBalance(boolean paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4, byte[] paramArrayOfByte, int paramInt5, int paramInt6);

    public native void ColorModeEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2);

    public native void CompositeColorEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void DrawEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2);

    public native void ExclusionEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ExclusionEx2(byte[] paramArrayOfByte, byte paramByte1, byte paramByte2, byte paramByte3, double paramDouble);

    public native void FaceBeauty(int[] paramArrayOfInt, int paramInt1, int paramInt2, int paramInt3);

    public native void FaceBeautyRelease();

    public native void FrameXCBK(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, int paramInt3);

    public native void GaussIIRBlurBrush(int[] paramArrayOfInt, int paramInt1, int paramInt2, int paramInt3, int paramInt4);

    public native void GaussIIRBlurImage(byte[] paramArrayOfByte, int paramInt1, int paramInt2, int paramInt3, int paramInt4);

    public native double GetDegreeByPoints(int paramInt1, int paramInt2, int paramInt3, int paramInt4);

    public native void Grayscale(byte[] paramArrayOfByte, int paramInt1, int paramInt2);

    public native void HardlightEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageColorBurnEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2);

    public native void ImageDarkenEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageExclusionEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageLightenEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageNormalEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageOverlayEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageScreenEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void ImageSoftLightEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void LOMO1(int[] paramArrayOfInt1, int paramInt1, int paramInt2, int[] paramArrayOfInt2);

    public native void LOMO2(int[] paramArrayOfInt1, int paramInt1, int paramInt2, int[] paramArrayOfInt2);

    public native void LightEnEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void MakeAllTransparent(byte[] paramArrayOfByte, int paramInt1, int paramInt2);

    public native void MultipleEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void NoiseEx(byte[] paramArrayOfByte, long paramLong);

    public native void NormalEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void OldImage(byte[] paramArrayOfByte1, int paramInt1, int paramInt2, byte[] paramArrayOfByte2, int paramInt3, int paramInt4);

    public native void PinLightEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2);

    public native void PtChangeByRotate(byte[] paramArrayOfByte, double paramDouble1, double paramDouble2, double paramDouble3);

    public native void RGBtoXYZ(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte);

    public native void RGBtoYIQ(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte);

    public native void RGBtoYUV(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte);

    public native void Resample(byte[] paramArrayOfByte1, int paramInt1, int paramInt2, int paramInt3, byte[] paramArrayOfByte2, int paramInt4, int paramInt5);

    public native void SSkinbeautify(int[] paramArrayOfInt, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, double paramDouble);

    public native void ScreenEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void SetBackWeakRadius(byte[] paramArrayOfByte, int paramInt1, int paramInt2);

    public native void SetColorImage(byte[] paramArrayOfByte, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5);

    public native void SetGrayScaleEx(byte[] paramArrayOfByte);

    public native void Sharp(int[] paramArrayOfInt, int paramInt1, int paramInt2, float paramFloat1, float paramFloat2);

    public native void SharpPreview(int[] paramArrayOfInt, int paramInt1, int paramInt2, float paramFloat1, float paramFloat2);

    public native void SharpPreviewRelease();

    public native void ShiftRGBEx(byte[] paramArrayOfByte, byte paramByte1, byte paramByte2, byte paramByte3);

    public native void SkinWhite(int[] paramArrayOfInt, int paramInt1, int paramInt2, int paramInt3);

    public native void SoftLightEx(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2, double paramDouble);

    public native void StyleBaoColor(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleCinnamon(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleClassic(int[] paramArrayOfInt, int paramInt1, int paramInt2, double paramDouble);

    public native void StyleClassicStudio(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleEP1(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleEP2(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleElegant(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleElegantNew(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleFP1(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleFP2(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleFilm(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleGP1(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, byte[] paramArrayOfByte, int paramInt3);

    public native void StyleGP2(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, byte[] paramArrayOfByte, int paramInt3);

    public native void StyleImpression(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleJapanese(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleLomoAP1(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, byte[] paramArrayOfByte, int paramInt3);

    public native void StyleLomoAP2(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, byte[] paramArrayOfByte, int paramInt3);

    public native void StyleLomoB(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleLomoBrightRed(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleLomoC(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleLomoChristmas(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleLomoHDR(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void StyleMilk1(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleMilk2(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleMilk3(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleMilk4(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleOldPhoto(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2);

    public native void StyleOldPhotoP1(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, byte[] paramArrayOfByte, int paramInt3);

    public native void StyleOldPhotoP2(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2, byte[] paramArrayOfByte, int paramInt3);

    public native void StyleRetro(int[] paramArrayOfInt, int paramInt1, int paramInt2);

    public native void XYZtoRGB(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte);

    public native void YIQtoRGB(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte);

    public native void YUVtoRGB(byte paramByte1, byte paramByte2, byte paramByte3, byte[] paramArrayOfByte);

    public native int add(int paramInt, byte paramByte);

    public native byte[] deal(byte[] paramArrayOfByte, int paramInt1, int paramInt2, int paramInt3, int paramInt4, String paramString);

}

/* Location:           C:\Users\LiFZhe\Desktop\mtxx_dex2jar.jar
 * Qualified Name:     com.mt.mtxx.image.JNI
 * JD-Core Version:    0.6.0
 */
```

这个对象里面包含了所以对图片处理的native方法，我们把这个对象以及他的完成包名全部复制到我们的项目中。

3、编写我们的MainActivity，在里面调用JNI实现对图片的美化功能

```java
package com.afinalstone.administrator.ndk_06_decompilation;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.mt.mtxx.image.JNI;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("mtimage-jni");
    }

    private ImageView imageView_result;
    private JNI jni;
    private Bitmap bitmap;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageView_result = (ImageView) findViewById(R.id.imageView_result);
        jni = new JNI();
        InputStream is = getResources().openRawResource(R.mipmap.timg);
        bitmap = BitmapFactory.decodeStream(is);
    }

    public void onClick(View view){
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
        jni.StyleLomoB(pixels, width, height);
        // 用处理好的像素数组 创建一张新的图片就是经过特效处理的
        Bitmap bitmap_result = Bitmap.createBitmap(pixels, width, height, bitmap.getConfig());
        imageView_result.setImageBitmap(bitmap_result);
    }
}

```

代码中可知，我们首先在static静态代码块加载库文件，然后初始化一个JNI的对象，并获取到图片资源文件timg的Bitmap对象，
接着在按钮的点击事件中对获取到的bitmap进行处理，然后重新设置给下面的ImageView控件，效果图如下：

![效果图](pic/效果图.png)

四、分析

早期的apk并没有现在放黑加固加壳之类的防范措施，我们可以清除的看到项目的入口是TopViewActivity：

1、TopViewActivity的关键代码：

```markdown
public class TopViewActivity
  extends Activity
{
  public static int backID;
  public int Background;
  private Button btn_about;
  //注释：对应“美化图片”按钮
  private Button btn_beautyPic;
  private Button btn_newboyhelp;
  private Button btn_set;
  private TextView btn_versionName;
  private LinearLayout buttonsLayout;

  ...代码省略...

  public void onCreate(Bundle paramBundle)
  {
    getWindow().setFlags(1024, 1024);
    super.onCreate(paramBundle);
    setContentView(2130903055);
    findView();
    this.tipAnimation = AnimationUtils.loadAnimation(this, 2130968592);
    //注释：为“美化图片”按钮设置点击事件
    this.btn_beautyPic.setOnClickListener(new OnClickListenerBeautyPic());
    this.btn_beautyPic.setOnTouchListener(new OnTouchListenerBeautyPic());
    this.btn_newboyhelp.setOnTouchListener(new OnTouchListenerNewboyhelp());
    this.btn_newboyhelp.setOnClickListener(new OnClickListenerNewboyhelp());
    this.btn_about.setOnTouchListener(new OnTouchListenerAbout());
    this.btn_about.setOnClickListener(new OnClickListenerAbout());
    this.btn_set.setOnTouchListener(new OnTouchListenerSet());
    this.btn_set.setOnClickListener(new OnClickListenerSet());
    getName();
    this.btn_versionName.setText(this.versionName + " 正式版");
    this.btn_versionName.setTextSize(12.0F);
  }
  
  ...代码省略...
  
  class OnClickListenerBeautyPic
    implements View.OnClickListener
  {
    OnClickListenerBeautyPic() {}
    
    public void onClick(View paramView)
    {
       //注释：这里是“美化图片”按钮的点击事件，打开ChoosePicActivity页面,这样我们就去看ChoosePicActivity的具体代码
      paramView = new Intent(TopViewActivity.this, ChoosePicActivity.class);
      TopViewActivity.this.startActivity(paramView);
      TopViewActivity.this.overridePendingTransition(2130968576, 2130968577);
    }
  }
  
  ...代码省略...

}
```

上面代码我们可以知道对“美化图片”按钮进行点击事件设置，开启了一个名叫ChoosePicActivity的新Activity。

2、ChoosePicActivity的关键代码：

```java

public class ChoosePicActivity
  extends Activity
{
   //注释：弹出一个选择图片的对话框
  private ChoosePicDialog mChooseDialog;

  
  private void setBtns()
  {
    ImageTestButton localImageTestButton1 = (ImageTestButton)findViewById(2131230785);
    ImageTestButton localImageTestButton2 = (ImageTestButton)findViewById(2131230786);
    ImageTestButton localImageTestButton3 = (ImageTestButton)findViewById(2131230787);
    ImageTestButton localImageTestButton4 = (ImageTestButton)findViewById(2131230788);
    ImageTestButton localImageTestButton5 = (ImageTestButton)findViewById(2131230789);
    localImageTestButton1.setResources(2130837588, 2130837589);
    localImageTestButton2.setResources(2130837586, 2130837587);
    localImageTestButton3.setResources(2130837594, 2130837595);
    localImageTestButton4.setResources(2130837590, 2130837591);
    localImageTestButton5.setResources(2130837592, 2130837593);
  }

  //这里在弹出ChoosePicDialog选择对话框之后，会使用startActivityForResult打开系统选择相册的页面，
  //然后在这里获取到具体的回调结果，可以拿到用户选择的图片具体路径
  protected void onActivityResult(int paramInt1, int paramInt2, Intent paramIntent)
  {
    do
    {
      do
      {
        try
        {
          MTDebug.Print("requestCode=" + paramInt1 + " resultCode=" + paramInt2);
          if ((paramInt1 != 0) || (paramInt2 != -1)) {
            continue;
          }
          if (this.mChooseDialog != null)
          {
            this.mChooseDialog.dismiss();
            this.mChooseDialog = null;
          }
          MtxxActivity.fromCamera = true;
          toMtxxActivity();
        }
        catch (Exception localException1)
        {
          for (;;)
          {
            Uri localUri;
            Cursor localCursor;
            localException1.printStackTrace();
            continue;
            try
            {
              MtxxActivity.loadPic = true;
              MyData.picSourceType = 0;
              toMtxxActivity();
            }
            catch (Exception localException2)
            {
              localException2.printStackTrace();
            }
            continue;
            if (localException2 != null)
            {
              String str = localException2.getPath();
              MTDebug.Print("path=" + str);
              MyData.strPicPath = str;
              try
              {
                MyData.bmpDst = null;
                System.gc();
                MtxxActivity.loadPic = true;
                MyData.picSourceType = 0;
                toMtxxActivity();
              }
              catch (Exception localException3)
              {
                localException3.printStackTrace();
              }
            }
          }
        }
        super.onActivityResult(paramInt1, paramInt2, paramIntent);
        return;
      } while ((paramInt1 != 1) || (paramInt2 != -1));
      if (this.mChooseDialog != null)
      {
        this.mChooseDialog.dismiss();
        this.mChooseDialog = null;
      }
    } while (paramIntent == null);
    localUri = paramIntent.getData();
    localCursor = getContentResolver().query(localUri, null, null, null, null);
    if (localCursor != null)
    {
      localCursor.moveToFirst();
      MyData.strPicPath = localCursor.getString(1);
      MTDebug.Print("MyData.strPicPath      " + MyData.strPicPath);
      if (!new File(MyData.strPicPath).exists())
      {
        finish();
        Toast.makeText(this, "加载图片失败", 0).show();
        MyPro.allScan(this);
        return;
      }
    }
  }
  
  protected void onCreate(Bundle paramBundle)
  {
    getWindow().setFlags(1024, 1024);
    super.onCreate(paramBundle);
    setContentView(2130903046);
    System.gc();
    setBtns();//设置按钮的显示样式
    this.mChooseDialog = new ChoosePicDialog(this);
    this.mChooseDialog.setDisplay();//创建一个ChoosePicDialog对话框并显示出来
    MTDebug.memeryUsed("ChoosePicActivity onCreate");
  }

   ...代码省略...
  
  //注释：进入到美图秀秀的具体效果设置修改页面，我们接着查看MtxxActivity的具体代码
  public void toMtxxActivity()
  {
    try
    {
      Intent localIntent = new Intent();
      localIntent.setClass(this, MtxxActivity.class);
      startActivity(localIntent);
      finish();
      overridePendingTransition(2130968577, 2130968578);
      return;
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
    }
  }
}


````

3、ChoosePicDialog对话框的具体代码

```java

public class ChoosePicDialog
  extends Dialog
  implements View.OnClickListener, View.OnTouchListener
{
  private static Context context;
  public static Window window = null;
  //注释：这个按钮是我们需要的，对应“从相册中选择”按钮，我们查看他的点击事件
  private Button btn_choosePic_choosePic = null;
  private Button btn_choosePic_photograph = null;
  private Button btn_choosePic_returnLast = null;
  private Button btn_choosePic_returnMainView = null;
  private File f;
  private boolean isProcessing = false;
  private String lastPicPath;
  
  public ChoosePicDialog(Context paramContext)
  {
    super(paramContext);
    context = paramContext;
  }
  
  private void findView()
  {
    this.btn_choosePic_returnLast = ((Button)findViewById(2131230727));
    this.btn_choosePic_choosePic = ((Button)findViewById(2131230729));
    this.btn_choosePic_photograph = ((Button)findViewById(2131230731));
    this.btn_choosePic_returnMainView = ((Button)findViewById(2131230733));
  }
  
  private void initData()
  {
    try
    {
      MyData.m_optMiddle.m_pHistory = OptHistoryTools.ReadOptHistory();
      if (MyData.m_optMiddle.m_pHistory != null)
      {
        String str = MyData.m_optMiddle.m_pHistory.GetPicPath(MyData.m_optMiddle.m_pHistory.m_nDoneListPos);
        if (str != null)
        {
          MTDebug.Print("returnLastOpt index=" + str);
          this.lastPicPath = ("/sdcard/.MTXX/HISTORY/" + str + ".jpg");
          this.f = new File(this.lastPicPath);
          MTDebug.Print("MyData.m_optMiddle.m_pHistory.strPicPath" + MyData.m_optMiddle.m_pHistory.getStrPicPath());
          MyData.strPicPath = MyData.m_optMiddle.m_pHistory.getStrPicPath();
          MyData.fScaleCut = MyData.m_optMiddle.m_pHistory.getfScaleCut();
          MyData.nPicDstWidth = MyData.m_optMiddle.m_pHistory.getnPicDstWidth();
          if ((this.f.exists()) && (MyData.strPicPath != null)) {
            return;
          }
          MTDebug.Print("File is null");
          this.btn_choosePic_returnLast.setBackgroundResource(2130837597);
          this.btn_choosePic_returnLast.setEnabled(false);
          return;
        }
      }
      this.btn_choosePic_returnLast.setBackgroundResource(2130837597);
      this.btn_choosePic_returnLast.setEnabled(false);
      return;
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
    }
  }

 ...代码省略...
  
  private void setListener()
  {
    this.btn_choosePic_returnLast.setOnClickListener(this);
    //设置按钮点击事件
    this.btn_choosePic_choosePic.setOnClickListener(this);
    this.btn_choosePic_photograph.setOnClickListener(this);
    this.btn_choosePic_returnMainView.setOnClickListener(this);
    this.btn_choosePic_returnLast.setOnTouchListener(this);
    this.btn_choosePic_choosePic.setOnTouchListener(this);
    this.btn_choosePic_photograph.setOnTouchListener(this);
    this.btn_choosePic_returnMainView.setOnTouchListener(this);
  }
  
  //注释：这里使用startActivityForResult选择图片之后，获取到图片的具体路径，然后回回调给之前的ChooseActivity的onActivityResult方法中
  public void choosePic()
  {
    try
    {
      Intent localIntent = new Intent();
      localIntent.setType("image/*");
      localIntent.setAction("android.intent.action.GET_CONTENT");
      ((Activity)context).startActivityForResult(localIntent, 1);
      return;
    }
    catch (Exception localException)
    {
      localException.printStackTrace();
    }
  }

   //注释：按钮响应事件，
  public void onClick(View paramView)
  {
    if (this.isProcessing) {
      return;
    }
    this.isProcessing = true;
    if (paramView.getId() == 2131230727) {
      returnLastOpt(context);
    }
    for (;;)
    {
      this.isProcessing = false;
      return;
      if (paramView.getId() == 2131230729)
      {
      //注释：按钮响应事件，选择图片
        choosePic();
      }
      else if (paramView.getId() == 2131230731)
      {
        photograph(context);
      }
      else if (paramView.getId() == 2131230733)
      {
        dismiss();
        ((Activity)context).finish();
        ((Activity)context).overridePendingTransition(2130968577, 2130968578);
      }
    }
  }
  

 ...代码省略...
  
  public void setDisplay()
  {
    setContentView(2130903041);
    setProperty();  //设置样式
    findView();     //findViewById
    setListener();  //设置监听事件
    initData();     //初始化相关数据
    show();         //先是选择图片的对话框
  }

  public void setProperty()
  {
    window = getWindow();
    WindowManager.LayoutParams localLayoutParams = window.getAttributes();
    localLayoutParams.x = 0;
    localLayoutParams.y = 0;
    window.setBackgroundDrawableResource(2130837513);
    window.setAttributes(localLayoutParams);
  }

}

```





最近碰见了一个错误： 
ibhyphenate_av.so: has text relocations 

错误产生的原因是 在 小米 Android 6.0系统中，app安装成功后 点击无法启动app。 

当时没有设备，无法进行调试。 后来调试后发现 不是无法启动app。而是启动app 的时候瞬间就崩溃了。 然后什么提示都没有 就给用户产生了一个 点击无法启动app 的错觉。

联机调试后 发现错误就是上面的那个了。

前面的那个so库是环信的支持库。 

解决方法：

将 targetSdkVersion 的值调整为23以下就可以了。 主要是因为环信的so库生成的时候的targetSdkVersion过低 没有达到23.所以就会出现了这个错误。

而去这个错误，在6.0以下的手机中你是测试不出来的。只有在6.0以上的系统才会出现这个bug。

总结： 如果使用了第三方的so库那么 就得注意你自己的targetSdkVersio 的值了。 


步骤1：
  class OnClickListenerBeautyPic
    implements View.OnClickListener
  {
    OnClickListenerBeautyPic() {}
    
    public void onClick(View paramView)
    {
      paramView = new Intent(TopViewActivity.this, ChoosePicActivity.class);
      TopViewActivity.this.startActivity(paramView);
      TopViewActivity.this.overridePendingTransition(2130968576, 2130968577);
    }
  }