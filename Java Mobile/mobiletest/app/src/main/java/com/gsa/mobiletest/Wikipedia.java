package com.gsa.mobiletest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebView;

public class Wikipedia extends AppCompatActivity {
    private WebView webView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wikipedia);

        webView = (WebView) findViewById(R.id.webView);
        webView.loadUrl("https://en.wikipedia.org/wiki/2016%E2%80%9317_UEFA_Champions_League");
    }
}
