plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")

    id("dagger.hilt.android.plugin")
    kotlin("kapt")
}

android {
    namespace = "com.tm.tests"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.tm.tests"
        minSdk = 21
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
    buildFeatures {
        compose = true
    }
    composeOptions {
        //kotlinCompilerExtensionVersion = "1.4.3"
        kotlinCompilerExtensionVersion = "1.5.3"
    }
    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
}

dependencies {

    // Core Compose Libraries
    implementation("androidx.activity:activity-compose:1.7.2")
    implementation("androidx.compose.ui:ui:1.5.3")
    implementation("androidx.compose.material:material:1.5.3")
    implementation("androidx.compose.ui:ui-tooling-preview:1.5.3")
    // Navigation Compose
    implementation("androidx.navigation:navigation-compose:2.7.3")
    // Hilt for Dependency Injection
    implementation("com.google.dagger:hilt-android:2.48")
    implementation("androidx.appcompat:appcompat:1.7.0")
    implementation("com.google.android.material:material:1.12.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    //implementation("androidx.media3:media3-common-ktx:1.4.1")
    kapt("com.google.dagger:hilt-android-compiler:2.48")
    // Kotlin Coroutines
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-android:1.7.3")
    // Coil (Image Loading)
    implementation("io.coil-kt:coil-compose:2.4.0")
    // Retrofit (API Calls)
    implementation("com.squareup.retrofit2:retrofit:2.9.0")
    implementation("com.squareup.retrofit2:converter-gson:2.9.0")
    // ViewModel & LiveData
    implementation("androidx.lifecycle:lifecycle-viewmodel-compose:2.6.2")
    implementation("androidx.lifecycle:lifecycle-livedata-ktx:2.6.2")
    // JUnit for Testing
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
    // Compose Material3
    implementation("androidx.compose.material3:material3:1.2.1") // Remplacez par la dernière version
    //for icons
    implementation("androidx.compose.material:material-icons-extended:1.5.0")
    //for Status bar control
    implementation("com.google.accompanist:accompanist-systemuicontroller:0.20.0")
    //Images
    implementation ("com.github.bumptech.glide:compose:1.0.0-alpha.1")
    //Async Image Loader
    implementation("io.coil-kt:coil-compose:2.2.2")
    // pager
    implementation("com.google.accompanist:accompanist-pager:0.32.0")
    implementation("com.google.accompanist:accompanist-pager-indicators:0.32.0")
    //
    implementation("com.google.accompanist:accompanist-insets:0.28.0")
    // video player
    implementation("androidx.media3:media3-exoplayer:1.2.0")
    implementation("androidx.media3:media3-ui:1.2.0")
    // video framer
    implementation("io.coil-kt:coil-compose:2.1.0")
    implementation("io.coil-kt:coil-video:2.1.0") // Pour supporter les frames vidéo

    //fragments
    implementation("androidx.fragment:fragment-ktx:1.6.1")






    implementation("androidx.appcompat:appcompat:1.7.0")
    implementation("com.google.android.material:material:1.12.0")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.2.1")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.6.1")

    implementation("com.ttt.api:TModeler:T1.0.25")
    implementation("com.ttt.api:T-System:1.0.1-T")
}