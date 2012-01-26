package com.vanillabreeze.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.util.ArrayList;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.AssetManager.AssetInputStream;
import android.util.Log;

public class XMLParsing {

	final static String TAG = "XMLParsing";

	public static ArrayList<XMLData> getData(Context context) {
		AssetManager assetManager = context.getResources().getAssets();
		AssetInputStream ais = null;
		StringBuilder stringBuilder = null;
		try {
			ais = (AssetInputStream) assetManager.open("factory.xml");
			BufferedReader br = new BufferedReader(new InputStreamReader(ais));
			String line = null;
			stringBuilder = new StringBuilder();
			while ((line = br.readLine()) != null) {
				stringBuilder.append(line);
				// Log.i("getXML", "" + line);
			}
		} catch (IOException e) {
			Log.e(TAG, "" + e.getMessage());
		}

		ArrayList<XMLData> xmlData = new ArrayList<XMLData>();
		try {

			XmlPullParserFactory parserCreator = XmlPullParserFactory.newInstance();
			parserCreator.setNamespaceAware(true);
			XmlPullParser parser = parserCreator.newPullParser();

			parser.setInput(new StringReader(stringBuilder.toString()));

			String tag = "";
			String current = "";
			int parserEvent = parser.getEventType();
			boolean inTitle = false;
			boolean toggle = false;
			XMLData data = null;

			while (parserEvent != XmlPullParser.END_DOCUMENT) {
				switch (parserEvent) {
				case XmlPullParser.TEXT:
					try {
						if (inTitle && toggle) {
							if (tag.compareTo(current) == 0) {
								toggle = false;
							}
							if (tag.compareTo("Stage_id") == 0) {
								// Log.i(TAG, "Stage_id = " + parser.getText());
								data.stages = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceCream_num") == 0) {
								// Log.i(TAG, "IceCream_num = " + parser.getText());
								data.icenum = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_a1") == 0) {
								// Log.i(TAG, "IceBall_a1 = " + parser.getText());
								data.icecreamball[0] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_a2") == 0) {
								// Log.i(TAG, "IceBall_a2 = " + parser.getText());
								data.icecreamball[1] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_a3") == 0) {
								// Log.i(TAG, "IceBall_a3 = " + parser.getText());
								data.icecreamball[2] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_b1") == 0) {
								// Log.i(TAG, "IceBall_b1 = " + parser.getText());
								data.icecreamball[3] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_b2") == 0) {
								// Log.i(TAG, "IceBall_b2 = " + parser.getText());
								data.icecreamball[4] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_b3") == 0) {
								// Log.i(TAG, "IceBall_b3 = " + parser.getText());
								data.icecreamball[5] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_c1") == 0) {
								// Log.i(TAG, "IceBall_c1 = " + parser.getText());
								data.icecreamball[6] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_c2") == 0) {
								// Log.i(TAG, "IceBall_c2 = " + parser.getText());
								data.icecreamball[7] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_c3") == 0) {
								// Log.i(TAG, "IceBall_c3 = " + parser.getText());
								data.icecreamball[8] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_d1") == 0) {
								// Log.i(TAG, "IceBall_d1 = " + parser.getText());
								data.icecreamball[9] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_d2") == 0) {
								// Log.i(TAG, "IceBall_d2 = " + parser.getText());
								data.icecreamball[10] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBall_d3") == 0) {
								// Log.i(TAG, "IceBall_d3 = " + parser.getText());
								data.icecreamball[11] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_a1") == 0) {
								// Log.i(TAG, "IceBallTwo_a1 = " + parser.getText());
								data.icecreamballTwo[0] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_a2") == 0) {
								// Log.i(TAG, "IceBallTwo_a2 = " + parser.getText());
								data.icecreamballTwo[1] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_a3") == 0) {
								// Log.i(TAG, "IceBallTwo_a3 = " + parser.getText());
								data.icecreamballTwo[2] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_b1") == 0) {
								// Log.i(TAG, "IceBallTwo_b1 = " + parser.getText());
								data.icecreamballTwo[3] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_b2") == 0) {
								// Log.i(TAG, "IceBallTwo_b2 = " + parser.getText());
								data.icecreamballTwo[4] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_b3") == 0) {
								// Log.i(TAG, "IceBallTwo_b3 = " + parser.getText());
								data.icecreamballTwo[5] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_c1") == 0) {
								// Log.i(TAG, "IceBallTwo_c1 = " + parser.getText());
								data.icecreamballTwo[6] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_c2") == 0) {
								// Log.i(TAG, "IceBallTwo_c2 = " + parser.getText());
								data.icecreamballTwo[7] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_c3") == 0) {
								// Log.i(TAG, "IceBallTwo_c3 = " + parser.getText());
								data.icecreamballTwo[8] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_d1") == 0) {
								// Log.i(TAG, "IceBallTwo_d1 = " + parser.getText());
								data.icecreamballTwo[9] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_d2") == 0) {
								// Log.i(TAG, "IceBallTwo_d2 = " + parser.getText());
								data.icecreamballTwo[10] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceBallTwo_d3") == 0) {
								// Log.i(TAG, "IceBallTwo_d3 = " + parser.getText());
								data.icecreamballTwo[11] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatterns") == 0) {
								// Log.i(TAG, "IcePatterns = " + parser.getText());
								data.icepattern = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("IcePattern_a1") == 0) {
								// Log.i(TAG, "IcePattern_a1 = " + parser.getText());
								data.icecreamPattern[0] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_a2") == 0) {
								// Log.i(TAG, "IcePattern_a2 = " + parser.getText());
								data.icecreamPattern[1] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_a3") == 0) {
								// Log.i(TAG, "IcePattern_a3 = " + parser.getText());
								data.icecreamPattern[2] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_b1") == 0) {
								// Log.i(TAG, "IcePattern_b1 = " + parser.getText());
								data.icecreamPattern[3] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_b2") == 0) {
								// Log.i(TAG, "IcePattern_b2 = " + parser.getText());
								data.icecreamPattern[4] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_b3") == 0) {
								// Log.i(TAG, "IcePattern_b3 = " + parser.getText());
								data.icecreamPattern[5] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_c1") == 0) {
								// Log.i(TAG, "IcePattern_c1 = " + parser.getText());
								data.icecreamPattern[6] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_c2") == 0) {
								// Log.i(TAG, "IcePattern_c2 = " + parser.getText());
								data.icecreamPattern[7] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_c3") == 0) {
								// Log.i(TAG, "IcePattern_c3 = " + parser.getText());
								data.icecreamPattern[8] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_d1") == 0) {
								// Log.i(TAG, "IcePattern_d1 = " + parser.getText());
								data.icecreamPattern[9] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_d2") == 0) {
								// Log.i(TAG, "IcePattern_d2 = " + parser.getText());
								data.icecreamPattern[10] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePattern_d3") == 0) {
								// Log.i(TAG, "IcePattern_d3 = " + parser.getText());
								data.icecreamPattern[11] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternsTwo") == 0) {
								// Log.i(TAG, "IcePatternsTwo = " + parser.getText());
								data.icepatterntwo = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("IcePatternTwo_a1") == 0) {
								// Log.i(TAG, "IcePatternTwo_a1 = " + parser.getText());
								data.icecreamPatternTwo[0] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_a2") == 0) {
								// Log.i(TAG, "IcePatternTwo_a2 = " + parser.getText());
								data.icecreamPatternTwo[1] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_a3") == 0) {
								// Log.i(TAG, "IcePatternTwo_a3 = " + parser.getText());
								data.icecreamPatternTwo[2] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_b1") == 0) {
								// Log.i(TAG, "IcePatternTwo_b1 = " + parser.getText());
								data.icecreamPatternTwo[3] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_b2") == 0) {
								// Log.i(TAG, "IcePatternTwo_b2 = " + parser.getText());
								data.icecreamPatternTwo[4] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_b3") == 0) {
								// Log.i(TAG, "IcePatternTwo_b3 = " + parser.getText());
								data.icecreamPatternTwo[5] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_c1") == 0) {
								// Log.i(TAG, "IcePatternTwo_c1 = " + parser.getText());
								data.icecreamPatternTwo[6] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_c2") == 0) {
								// Log.i(TAG, "IcePatternTwo_c2 = " + parser.getText());
								data.icecreamPatternTwo[7] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_c3") == 0) {
								// Log.i(TAG, "IcePatternTwo_c3 = " + parser.getText());
								data.icecreamPatternTwo[8] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_d1") == 0) {
								// Log.i(TAG, "IcePatternTwo_d1 = " + parser.getText());
								data.icecreamPatternTwo[9] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_d2") == 0) {
								// Log.i(TAG, "IcePatternTwo_d2 = " + parser.getText());
								data.icecreamPatternTwo[10] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IcePatternTwo_d3") == 0) {
								// Log.i(TAG, "IcePatternTwo_d3 = " + parser.getText());
								data.icecreamPatternTwo[11] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyes") == 0) {
								// Log.i(TAG, "IceEyes = " + parser.getText());
								data.iceeyes = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("IceEye_a1") == 0) {
								// Log.i(TAG, "IceEye_a1 = " + parser.getText());
								data.icecreamEye[0] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_a2") == 0) {
								// Log.i(TAG, "IceEye_a2 = " + parser.getText());
								data.icecreamEye[1] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_a3") == 0) {
								// Log.i(TAG, "IceEye_a3 = " + parser.getText());
								data.icecreamEye[2] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_a4") == 0) {
								// Log.i(TAG, "IceEye_a4 = " + parser.getText());
								data.icecreamEye[3] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_b1") == 0) {
								// Log.i(TAG, "IceEye_b1 = " + parser.getText());
								data.icecreamEye[4] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_b2") == 0) {
								// Log.i(TAG, "IceEye_b2 = " + parser.getText());
								data.icecreamEye[5] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_b3") == 0) {
								// Log.i(TAG, "IceEye_b3 = " + parser.getText());
								data.icecreamEye[6] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEye_b4") == 0) {
								// Log.i(TAG, "IceEye_b4 = " + parser.getText());
								data.icecreamEye[7] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyesTwo") == 0) {
								// Log.i(TAG, "IceEyesTwo = " + parser.getText());
								data.iceeyestwo = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("IceEyeTwo_a1") == 0) {
								// Log.i(TAG, "IceEyeTwo_a1 = " + parser.getText());
								data.icecreamEyeTwo[0] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_a2") == 0) {
								// Log.i(TAG, "IceEyeTwo_a2 = " + parser.getText());
								data.icecreamEyeTwo[1] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_a3") == 0) {
								// Log.i(TAG, "IceEyeTwo_a3 = " + parser.getText());
								data.icecreamEyeTwo[2] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_a4") == 0) {
								// Log.i(TAG, "IceEyeTwo_a4 = " + parser.getText());
								data.icecreamEyeTwo[3] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_b1") == 0) {
								// Log.i(TAG, "IceEyeTwo_b1 = " + parser.getText());
								data.icecreamEyeTwo[4] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_b2") == 0) {
								// Log.i(TAG, "IceEyeTwo_b2 = " + parser.getText());
								data.icecreamEyeTwo[5] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_b3") == 0) {
								// Log.i(TAG, "IceEyeTwo_b3 = " + parser.getText());
								data.icecreamEyeTwo[6] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceEyeTwo_b4") == 0) {
								// Log.i(TAG, "IceEyeTwo_b4 = " + parser.getText());
								data.icecreamEyeTwo[7] = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("MilkCream") == 0) {
								// Log.i(TAG, "MilkCream = " + parser.getText());
								data.milkcream = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("Cherry") == 0) {
								// Log.i(TAG, "Cherry = " + parser.getText());
								data.cherry = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("Chocochips") == 0) {
								// Log.i(TAG, "Chocochips = " + parser.getText());
								data.chocochips = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("Nuts") == 0) {
								// Log.i(TAG, "Nuts = " + parser.getText());
								data.nuts = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("Candy") == 0) {
								// Log.i(TAG, "Candy = " + parser.getText());
								data.candy = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("LeftSpoid") == 0) {
								// Log.i(TAG, "LeftSpoid = " + parser.getText());
								data.leftspoid = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("RightSpoid") == 0) {
								// Log.i(TAG, "RightSpoid = " + parser.getText());
								data.rightspoid = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("IceIce") == 0) {
								// Log.i(TAG, "IceIce = " + parser.getText());
								data.iceice = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("LeftCornCount") == 0) {
								// Log.i(TAG, "LeftCornCount = " + parser.getText());
								data.leftcorncount = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("LeftCorn_V") == 0) {
								// Log.i(TAG, "LeftCorn_V = " + parser.getText());
								data.leftcorn_v = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("LeftCorn_C") == 0) {
								// Log.i(TAG, "LeftCorn_C = " + parser.getText());
								data.leftcorn_c = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("LeftCorn_B") == 0) {
								// Log.i(TAG, "LeftCorn_B = " + parser.getText());
								data.leftcorn_b = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("LeftCorn_G") == 0) {
								// Log.i(TAG, "LeftCorn_G = " + parser.getText());
								data.leftcorn_g = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("RightCornCount") == 0) {
								// Log.i(TAG, "RightCornCount = " + parser.getText());
								data.rightcorncount = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("RightCorn_V") == 0) {
								// Log.i(TAG, "RightCorn_V = " + parser.getText());
								data.rightcorn_v = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("RightCorn_C") == 0) {
								// Log.i(TAG, "RightCorn_C = " + parser.getText());
								data.rightcorn_c = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("RightCorn_B") == 0) {
								// Log.i(TAG, "RightCorn_B = " + parser.getText());
								data.rightcorn_b = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("RightCorn_G") == 0) {
								// Log.i(TAG, "RightCorn_G = " + parser.getText());
								data.rightcorn_g = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("CenterCornCount") == 0) {
								// Log.i(TAG, "CenterCornCount = " + parser.getText());
								data.centercorncount = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("CenterCorn_V") == 0) {
								// Log.i(TAG, "CenterCorn_V = " + parser.getText());
								data.centercorn_v = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("CenterCorn_C") == 0) {
								// Log.i(TAG, "CenterCorn_C = " + parser.getText());
								data.centercorn_c = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("CenterCorn_B") == 0) {
								// Log.i(TAG, "CenterCorn_B = " + parser.getText());
								data.centercorn_b = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("CenterCorn_G") == 0) {
								// Log.i(TAG, "CenterCorn_G = " + parser.getText());
								data.centercorn_g = Integer.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("TUB_BIG_VANILLA") == 0) {
								// Log.i(TAG, "TUB_BIG_VANILLA = " + parser.getText());
								data.TUB_BIG_VANILLA = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_BIG_CHOCO") == 0) {
								// Log.i(TAG, "TUB_BIG_CHOCO = " + parser.getText());
								data.TUB_BIG_CHOCO = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_BIG_BERRY") == 0) {
								// Log.i(TAG, "TUB_BIG_BERRY = " + parser.getText());
								data.TUB_BIG_BERRY = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_BIG_GREEN") == 0) {
								// Log.i(TAG, "TUB_BIG_GREEN = " + parser.getText());
								data.TUB_BIG_GREEN = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_SMALL_VANILLA") == 0) {
								// Log.i(TAG, "TUB_SMALL_VANILLA = " + parser.getText());
								data.TUB_SMALL_VANILLA = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_SMALL_CHOCO") == 0) {
								// Log.i(TAG, "TUB_SMALL_CHOCO = " + parser.getText());
								data.TUB_SMALL_CHOCO = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_SMALL_BERRY") == 0) {
								// Log.i(TAG, "TUB_SMALL_BERRY = " + parser.getText());
								data.TUB_SMALL_BERRY = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("TUB_SMALL_GREEN") == 0) {
								// Log.i(TAG, "TUB_SMALL_GREEN = " + parser.getText());
								data.TUB_SMALL_GREEN = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_H_VANILLA") == 0) {
								// Log.i(TAG, "SPOON_H_VANILLA = " + parser.getText());
								data.SPOON_H_VANILLA = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_H_CHOCO") == 0) {
								// Log.i(TAG, "SPOON_H_CHOCO = " + parser.getText());
								data.SPOON_H_CHOCO = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_H_BERRY") == 0) {
								// Log.i(TAG, "SPOON_H_BERRY = " + parser.getText());
								data.SPOON_H_BERRY = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_H_GREEN") == 0) {
								// Log.i(TAG, "SPOON_H_GREEN = " + parser.getText());
								data.SPOON_H_GREEN = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_L_VANILLA") == 0) {
								// Log.i(TAG, "SPOON_L_VANILLA = " + parser.getText());
								data.SPOON_L_VANILLA = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_L_CHOCO") == 0) {
								// Log.i(TAG, "SPOON_L_CHOCO = " + parser.getText());
								data.SPOON_L_CHOCO = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_L_BERRY") == 0) {
								// Log.i(TAG, "SPOON_L_BERRY = " + parser.getText());
								data.SPOON_L_BERRY = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_L_GREEN") == 0) {
								// Log.i(TAG, "SPOON_L_GREEN = " + parser.getText());
								data.SPOON_L_GREEN = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_R_VANILLA") == 0) {
								// Log.i(TAG, "SPOON_R_VANILLA = " + parser.getText());
								data.SPOON_R_VANILLA = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_R_CHOCO") == 0) {
								// Log.i(TAG, "SPOON_R_CHOCO = " + parser.getText());
								data.SPOON_R_CHOCO = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_R_BERRY") == 0) {
								// Log.i(TAG, "SPOON_R_BERRY = " + parser.getText());
								data.SPOON_R_BERRY = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SPOON_R_GREEN") == 0) {
								// Log.i(TAG, "SPOON_R_GREEN = " + parser.getText());
								data.SPOON_R_GREEN = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("RING_VERTICAL") == 0) {
								// Log.i(TAG, "RING_VERTICAL = " + parser.getText());
								data.RING_VERTICAL = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("RING_HORIZON") == 0) {
								// Log.i(TAG, "RING_HORIZON = " + parser.getText());
								data.RING_HORIZON = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("SUNGLASS") == 0) {
								// Log.i(TAG, "SUNGLASS = " + parser.getText());
								data.SUNGLASS = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CAP_OBJ") == 0) {
								// Log.i(TAG, "CAP_OBJ = " + parser.getText());
								data.CAP_OBJ = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("ICE_OBJ") == 0) {
								// Log.i(TAG, "ICE_OBJ = " + parser.getText());
								data.ICE_OBJ = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("PATTERN_CAST") == 0) {
								// Log.i(TAG, "PATTERN_CAST = " + parser.getText());
								data.PATTERN_CAST = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("MIX_OBJ") == 0) {
								// Log.i(TAG, "MIX_OBJ = " + parser.getText());
								data.MIX_OBJ = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("MASK_OBJ") == 0) {
								// Log.i(TAG, "MASK_OBJ = " + parser.getText());
								data.MASK_OBJ = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterMilkCream") == 0) {
								// Log.i(TAG, "CenterMilkCream = " + parser.getText());
								data.CenterMilkCream = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterCherry") == 0) {
								// Log.i(TAG, "CenterCherry = " + parser.getText());
								data.CenterCherry = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterChocochips") == 0) {
								// Log.i(TAG, "CenterChocochips = " + parser.getText());
								data.CenterCherry = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterNuts") == 0) {
								// Log.i(TAG, "CenterNuts = " + parser.getText());
								data.CenterCherry = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterCandy") == 0) {
								// Log.i(TAG, "CenterCandy = " + parser.getText());
								data.CenterCherry = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterSpoid_v") == 0) {
								// Log.i(TAG, "CenterSpoid_v = " + parser.getText());
								data.CenterSpoid_v = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterSpoid_c") == 0) {
								// Log.i(TAG, "CenterSpoid_c = " + parser.getText());
								data.CenterSpoid_c = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterSpoid_b") == 0) {
								// Log.i(TAG, "CenterSpoid_b = " + parser.getText());
								data.CenterSpoid_b = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("CenterSpoid_g") == 0) {
								// Log.i(TAG, "CenterSpoid_g = " + parser.getText());
								data.CenterSpoid_g = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							} else if (tag.compareTo("DefaultTime") == 0) {
								// Log.i(TAG, "DefaultTime = " + parser.getText());
								data.DefaultTime = Float.valueOf(parser.getText());
								break;
							} else if (tag.compareTo("DefaultMove") == 0) {
								// Log.i(TAG, "DefaultMove = " + parser.getText());
								// data.defaultMove = Integer.valueOf(parser.getText());
								data.CenterCherry = Integer.valueOf(parser.getText()) >= 0 ? true : false;
								break;
							}

						}
					} catch (NumberFormatException e) {
						Log.e(TAG, "NumberFormatException : " + e.getMessage());
					}
					break;

				case XmlPullParser.END_TAG:
					tag = parser.getName();
					if (tag.compareTo("Stages") == 0) {
						// Log.i(TAG, "XmlPullParser.END_TAG:");
						inTitle = false;
						xmlData.add(data);
					}
					break;

				case XmlPullParser.START_TAG:

					tag = parser.getName();
					if (tag.compareTo("Stages") == 0) {
						// Log.i(TAG, "XmlPullParser.START_TAG:");
						inTitle = true;
						data = new XMLData();
					}

					current = tag;
					toggle = true;

					break;
				}

				parserEvent = parser.next();
				// parserEvent = parser.nextToken();
			}

		} catch (XmlPullParserException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

		return xmlData;
	}
}
