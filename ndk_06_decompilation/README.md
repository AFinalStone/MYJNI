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