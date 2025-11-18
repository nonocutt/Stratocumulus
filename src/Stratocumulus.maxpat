{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 9,
			"minor" : 0,
			"revision" : 0,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 168.0, 106.0, 1239.0, 1029.0 ],
		"gridsize" : [ 15.0, 15.0 ],
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "spectroscope~",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 726.0, 767.0, 300.0, 100.0 ]
				}

			}
, 			{
				"box" : 				{
					"basictuning" : 440,
					"clipheight" : 29.0,
					"data" : 					{
						"clips" : [ 							{
								"absolutepath" : "Macintosh HD:/Users/luma/Documents/School/Semester 7 (25FA)/EP-491 Adv Proj in Elec Prod & Dsgn/REPO/Week 2/TESTING AUDIO/AR_ZM_vocal_oneshot_haah_sustain_dry_B.wav",
								"filename" : "AR_ZM_vocal_oneshot_haah_sustain_dry_B.wav",
								"filekind" : "audiofile",
								"id" : "u287002551",
								"loop" : 0,
								"content_state" : 								{

								}

							}
, 							{
								"absolutepath" : "Macintosh HD:/Users/luma/Documents/School/Semester 7 (25FA)/EP-491 Adv Proj in Elec Prod & Dsgn/REPO/Week 2/TESTING AUDIO/AR_ZM_vocal_oneshot_lairy_long_sustain_dry_E.wav",
								"filename" : "AR_ZM_vocal_oneshot_lairy_long_sustain_dry_E.wav",
								"filekind" : "audiofile",
								"id" : "u024002556",
								"loop" : 1,
								"content_state" : 								{
									"loop" : 1
								}

							}
, 							{
								"absolutepath" : "Macintosh HD:/Users/luma/Documents/School/Semester 7 (25FA)/EP-491 Adv Proj in Elec Prod & Dsgn/REPO/Week 2/TESTING AUDIO/AR_ZM_vocal_oneshot_long_sustain_dry_G.wav",
								"filename" : "AR_ZM_vocal_oneshot_long_sustain_dry_G.wav",
								"filekind" : "audiofile",
								"id" : "u728002561",
								"loop" : 1,
								"content_state" : 								{
									"loop" : 1
								}

							}
, 							{
								"absolutepath" : "Macintosh HD:/Users/luma/Documents/School/Semester 7 (25FA)/EP-491 Adv Proj in Elec Prod & Dsgn/REPO/Week 2/TESTING AUDIO/fss_ecv2_138_vocal_adlib_dry_tone_high_sustained_Gb.wav",
								"filename" : "fss_ecv2_138_vocal_adlib_dry_tone_high_sustained_Gb.wav",
								"filekind" : "audiofile",
								"id" : "u361002566",
								"loop" : 0,
								"content_state" : 								{

								}

							}
, 							{
								"absolutepath" : "Macintosh HD:/Users/luma/Documents/School/Semester 7 (25FA)/EP-491 Adv Proj in Elec Prod & Dsgn/REPO/Week 2/TESTING AUDIO/SO_JC_vocal_note_sustain_G.wav",
								"filename" : "SO_JC_vocal_note_sustain_G.wav",
								"filekind" : "audiofile",
								"id" : "u865002571",
								"loop" : 0,
								"content_state" : 								{

								}

							}
 ]
					}
,
					"followglobaltempo" : 0,
					"formantcorrection" : 0,
					"id" : "obj-22",
					"maxclass" : "playlist~",
					"mode" : "basic",
					"numinlets" : 1,
					"numoutlets" : 5,
					"originallength" : [ 0.0, "ticks" ],
					"originaltempo" : 120.0,
					"outlettype" : [ "signal", "signal", "signal", "", "dictionary" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 726.0, 584.0, 150.0, 150.0 ],
					"pitchcorrection" : 0,
					"quality" : "basic",
					"saved_attribute_attributes" : 					{
						"candicane2" : 						{
							"expression" : ""
						}
,
						"candicane3" : 						{
							"expression" : ""
						}
,
						"candicane4" : 						{
							"expression" : ""
						}
,
						"candicane5" : 						{
							"expression" : ""
						}
,
						"candicane6" : 						{
							"expression" : ""
						}
,
						"candicane7" : 						{
							"expression" : ""
						}
,
						"candicane8" : 						{
							"expression" : ""
						}

					}
,
					"timestretch" : [ 0 ]
				}

			}
, 			{
				"box" : 				{
					"format" : 4,
					"id" : "obj-15",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 583.0, 200.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "ezadc~",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 423.0, 79.0, 45.0, 45.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 423.0, 343.0, 45.0, 45.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 423.0, 189.0, 48.0, 136.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.gain~",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_modmode" : 3,
							"parameter_osc_name" : "<default>",
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 663.0, 91.0, 40.0, 22.0 ],
					"text" : "midiin"
				}

			}
, 			{
				"box" : 				{
					"autosave" : 1,
					"bgcolor" : [ 0.176470588235294, 0.176470588235294, 0.176470588235294, 1.0 ],
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"id" : "obj-1",
					"inletInfo" : 					{
						"IOInfo" : [ 							{
								"type" : "signal",
								"index" : 1,
								"tag" : "in1",
								"comment" : ""
							}
, 							{
								"type" : "midi",
								"index" : -1,
								"tag" : "",
								"comment" : ""
							}
 ]
					}
,
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 4,
					"outletInfo" : 					{
						"IOInfo" : [ 							{
								"type" : "signal",
								"index" : 1,
								"tag" : "out1",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 2,
								"tag" : "out2",
								"comment" : ""
							}
, 							{
								"type" : "event",
								"index" : 3,
								"tag" : "out3",
								"comment" : ""
							}
 ]
					}
,
					"outlettype" : [ "signal", "signal", "", "list" ],
					"patching_rect" : [ 423.0, 151.0, 259.0, 22.0 ],
					"rnboattrcache" : 					{
						"Grain_Size" : 						{
							"label" : "Grain_Size",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Dry/Wet" : 						{
							"label" : "Dry/Wet",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Sustain" : 						{
							"label" : "Sustain",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Spread" : 						{
							"label" : "Spread",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Attack" : 						{
							"label" : "Attack",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Stereo" : 						{
							"label" : "Stereo",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Release" : 						{
							"label" : "Release",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Density" : 						{
							"label" : "Density",
							"isEnum" : 0,
							"parsestring" : ""
						}
,
						"Decay" : 						{
							"label" : "Decay",
							"isEnum" : 0,
							"parsestring" : ""
						}

					}
,
					"rnboversion" : "1.4.0",
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_invisible" : 1,
							"parameter_longname" : "rnbo~",
							"parameter_modmode" : 0,
							"parameter_osc_name" : "<default>",
							"parameter_shortname" : "rnbo~",
							"parameter_type" : 3
						}

					}
,
					"saved_object_attributes" : 					{
						"optimization" : "O1",
						"parameter_enable" : 1,
						"uuid" : "f2bc7c4b-4fb1-11f0-bc4b-e2e88603c870"
					}
,
					"snapshot" : 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "snapshotlist",
						"origin" : "rnbo~",
						"type" : "list",
						"subtype" : "Undefined",
						"embed" : 1,
						"snapshot" : 						{
							"Sustain" : 							{
								"value" : 100.0
							}
,
							"Release" : 							{
								"value" : 260.0
							}
,
							"__sps" : 							{
								"voice" : [ 									{

									}
, 									{

									}
, 									{

									}
, 									{

									}
, 									{

									}
, 									{

									}
, 									{

									}
, 									{

									}
 ]
							}
,
							"Attack" : 							{
								"value" : 200.0
							}
,
							"Stereo" : 							{
								"value" : 50.0
							}
,
							"Density" : 							{
								"value" : 15.0
							}
,
							"Dry/Wet" : 							{
								"value" : 72.0
							}
,
							"Decay" : 							{
								"value" : 200.0
							}
,
							"Grain_Size" : 							{
								"value" : 160.0
							}
,
							"Spread" : 							{
								"value" : 0.0
							}
,
							"__presetid" : "harmonizer.rnbopat"
						}
,
						"snapshotlist" : 						{
							"current_snapshot" : 0,
							"entries" : [ 								{
									"filetype" : "C74Snapshot",
									"version" : 2,
									"minorversion" : 0,
									"name" : "harmonizer.rnbopat",
									"origin" : "harmonizer.rnbopat",
									"type" : "rnbo",
									"subtype" : "",
									"embed" : 1,
									"snapshot" : 									{
										"Sustain" : 										{
											"value" : 100.0
										}
,
										"Release" : 										{
											"value" : 260.0
										}
,
										"__sps" : 										{
											"voice" : [ 												{

												}
, 												{

												}
, 												{

												}
, 												{

												}
, 												{

												}
, 												{

												}
, 												{

												}
, 												{

												}
 ]
										}
,
										"Attack" : 										{
											"value" : 200.0
										}
,
										"Stereo" : 										{
											"value" : 50.0
										}
,
										"Density" : 										{
											"value" : 15.0
										}
,
										"Dry/Wet" : 										{
											"value" : 72.0
										}
,
										"Decay" : 										{
											"value" : 200.0
										}
,
										"Grain_Size" : 										{
											"value" : 160.0
										}
,
										"Spread" : 										{
											"value" : 0.0
										}
,
										"__presetid" : "harmonizer.rnbopat"
									}
,
									"fileref" : 									{
										"name" : "harmonizer.rnbopat",
										"filename" : "harmonizer.rnbopat.maxsnap",
										"filepath" : "~/Documents/Max 9/Snapshots",
										"filepos" : -1,
										"snapshotfileid" : "bd4110558fcd01d83d9999846207c186"
									}

								}
 ]
						}

					}
,
					"text" : "rnbo~ harmonizer.rnbopat @parameter_enable",
					"varname" : "rnbo~"
				}

			}
, 			{
				"box" : 				{
					"attr" : "Attack",
					"id" : "obj-6",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.0, 55.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Decay",
					"id" : "obj-7",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.0, 79.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Sustain",
					"id" : "obj-8",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.0, 103.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Release",
					"id" : "obj-9",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.0, 127.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Density",
					"id" : "obj-13",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 214.0, 55.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Grain_Size",
					"id" : "obj-14",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 214.0, 79.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Spread",
					"id" : "obj-18",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 214.0, 103.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Stereo",
					"id" : "obj-19",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 214.0, 127.0, 150.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"attr" : "Dry/Wet",
					"id" : "obj-3",
					"maxclass" : "attrui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 532.0, 259.0, 150.0, 22.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-4", 1 ],
					"midpoints" : [ 512.5, 184.0, 461.5, 184.0 ],
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-4", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.9032142162323, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 223.5, 79.0, 200.5, 79.0, 200.5, 40.0, 407.5, 40.0, 407.5, 136.0, 432.5, 136.0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.9032142162323, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 223.5, 103.0, 200.5, 103.0, 200.5, 40.0, 407.5, 40.0, 407.5, 136.0, 432.5, 136.0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.9032142162323, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 223.5, 127.0, 200.5, 127.0, 200.5, 160.0, 407.5, 160.0, 407.5, 148.0, 432.5, 148.0 ],
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.9032142162323, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 223.5, 160.0, 407.5, 160.0, 407.5, 148.0, 432.5, 148.0 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.898102760314941, 0.850016474723816, 1.0 ],
					"destination" : [ "obj-1", 1 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 541.5, 282.0, 483.0, 282.0, 483.0, 174.0, 420.0, 174.0, 420.0, 147.0, 432.5, 147.0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-5", 1 ],
					"midpoints" : [ 439.75, 337.0, 458.5, 337.0 ],
					"source" : [ "obj-4", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-5", 0 ],
					"midpoints" : [ 432.5, 328.0, 432.5, 328.0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.940606951713562, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 42.5, 78.0, 18.0, 78.0, 18.0, 159.0, 408.0, 159.0, 408.0, 147.0, 432.5, 147.0 ],
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.940606951713562, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 42.5, 102.0, 18.0, 102.0, 18.0, 159.0, 408.0, 159.0, 408.0, 147.0, 432.5, 147.0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.940606951713562, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 42.5, 126.0, 30.0, 126.0, 30.0, 159.0, 408.0, 159.0, 408.0, 147.0, 432.5, 147.0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"color" : [ 0.940606951713562, 0.0, 0.0, 1.0 ],
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 42.5, 159.0, 408.0, 159.0, 408.0, 147.0, 432.5, 147.0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"originid" : "pat-24",
		"parameters" : 		{
			"obj-1" : [ "rnbo~", "rnbo~", 0 ],
			"obj-4" : [ "live.gain~", "live.gain~", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "harmonizer.rnbopat",
				"bootpath" : "~/Documents/School/Semester 7 25FA/EP-491 Adv Proj in Elec Prod & Dsgn/REPO/Max",
				"patcherrelativepath" : ".",
				"type" : "RBOP",
				"implicit" : 1
			}
, 			{
				"name" : "harmonizer.rnbopat.maxsnap",
				"bootpath" : "~/Documents/Max 9/Snapshots",
				"patcherrelativepath" : "../../../../../Max 9/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"toolbaradditions" : [ "packagemanager", "browsegendsp", "browsegenjit" ]
	}

}
