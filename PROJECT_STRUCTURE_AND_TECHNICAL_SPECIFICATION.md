# Smart Boiler Monitoring and Safety Management System (Boiler Black Box)
## Comprehensive Technical Architecture, Component Specifications, and Project Structure

---

### Executive Document Metadata
- **Project Name**: Smart Boiler Monitoring and Safety Management System (Boiler-Black-Box)
- **Document Type**: Comprehensive Technical Specification & Complete Repository Structure
- **Target Audience**: Industrial Automation Engineers, Embedded Systems Developers, Cloud Architects, Frontend Engineers, System Auditors
- **Release Version**: 1.0.0 (Production Web 1.0 & ESP32 Embedded Telemetry Stack)
- **Status**: Verified & Operational

---

## 1. Executive Summary & Problem Formulation

Industrial boiler systems are critical thermal generation assets in manufacturing, power utilities, chemical synthesis, and heavy manufacturing. Operating continuously under elevated thermal gradients (150°C – 300°C+) and severe hydraulic pressures (5 – 25+ bar), industrial boilers are susceptible to catastrophic mechanical failures, tube ruptures, thermal explosions, and scaling decay if operating limits are breached.

Conventional boiler monitoring predominantly relies on isolated mechanical gauges, localized analog readouts, or proprietary SCADA systems that lack regional oversight, real-time remote telemetry, automated safety classification, and multi-tenant authorization.

The **Smart Boiler Monitoring and Safety Management System** (termed **Boiler Black Box**) resolves these challenges through an integrated, multi-tier Industrial Internet of Things (IIoT) ecosystem:
1. **Edge Hardware Sensing**: Industrial microcontroller (ESP32) sampling multi-variable telemetry (temperature, pressure, volumetric flow, total dissolved solids).
2. **Secure Transport Messaging**: Transport Layer Security (TLS 1.2/1.3, port 8883) encrypted MQTT messaging via HiveMQ Cloud.
3. **Resilient Ingestion Bridge**: Node.js microservice performing strict schema validation, type enforcement, timestamp normalization, and bounded-retry persistence into Google Cloud Firestore.
4. **Zero-Trust Cloud Database**: Cloud Firestore secured by granular, role-based security rules guaranteeing strict data isolation between Regulatory Inspectors, Factory Owners, and Central System Administrators.
5. **Real-Time Reactive Web Interface**: Modern React 19 + Vite dashboard delivering sub-second live metric streaming, stale data detection watchdog timers, manual safety override tracking, and multi-boiler state visualization.

---

## 2. Complete Project Repository Structure

Below is the complete, exhaustive directory and file layout of the entire `Boiler-Black-Box` repository, mapping every single script, configuration file, source module, and image asset:

```text
Boiler-Black-Box/
├── .gitignore                                 # Git exclusions for node_modules, .env secrets, and build artifacts
├── README.md                                  # Repository overview, quick-start guide, and system showcase
├── PROJECT_STRUCTURE_AND_TECHNICAL_SPECIFICATION.md # Master comprehensive technical architecture & specifications
├── docs/                                      # Project documentation and visual media assets
│   └── images/                                # System showcase photographic and screenshot assets
│       ├── hardware-prototype.jpg             # Physical prototype rig: cylindrical boiler, sensors, ESP32, power rail
│       ├── dashboard-overview.jpg             # Multi-boiler live grid monitoring dashboard
│       ├── boiler-details-live.jpg            # Single-boiler real-time telemetry inspection interface (Boiler B01)
│       └── boiler-details-nodata.jpg          # Standby / offline boiler state interface (Boiler B03)
│
├── Boiler Dash HW component and code/         # Embedded firmware, crypto certificates, and prototype web client
│   ├── arduinoesp32.ino                       # ESP32 C++ Arduino firmware (Wi-Fi, TLS MQTTS, JSON serialization)
│   ├── Certificates.h                         # Amazon Root CA 1 X.509 certificate for HiveMQ TLS handshake
│   └── dashboard.html                         # Standalone zero-dependency HTML5/WSS live monitoring prototype
│
└── Boiler Web 1.0/                            # Production Web Application & Cloud Microservice Stack
    ├── package.json                           # Monorepo root automation scripts (dev, bridge, test, lint, build)
    ├── package-lock.json                      # Workspace lockfile for consistent dependency resolution
    ├── firebase.json                          # Firebase Hosting SPA rewrite configuration and Firestore target bindings
    ├── firestore.rules                        # Declarative Zero-Trust Role-Based Access Control (RBAC) security rules
    ├── firestore.indexes.json                 # Composite B-tree indexes for high-speed chronological queries
    ├── README.md                              # Web stack documentation, migration history, and MQTT payload contract
    │
    ├── boiler-mqtt-bridge/                    # Node.js 22 LTS Ingestion Microservice (MQTT to Firestore)
    │   ├── package.json                       # Service metadata and runtime dependencies (firebase-admin, mqtt)
    │   ├── package-lock.json                  # Locked dependency graph for bridge microservice
    │   ├── .env.example                       # Template for required environment secrets and broker endpoints
    │   ├── firebase.js                        # Firebase Admin SDK initialization and Service Account credential loader
    │   ├── index.js                           # Bridge core daemon: TLS MQTT subscriber, QoS 1 processor, retry engine
    │   ├── payload.js                         # Pure functional schema validator, type-coercion, and timestamp normalizer
    │   ├── payload.test.js                    # Unit tests for payload normalization, boundary cases, and invalid inputs
    │   ├── check_db.js                        # Database diagnostic script: queries and prints sample collection documents
    │   ├── create_users.js                    # Identity provisioning CLI: creates Auth accounts and UID-mapped user profiles
    │   ├── migrate_profiles.js                # Profile migration script: reconciles legacy user records to Auth UIDs
    │   └── smartboiler369-firebase-adminsdk-fbsvc-b899aa1b38.json # Local Google Cloud Service Account key (secured/ignored)
    │
    └── boiler-dashboard/                      # React 19 + Vite 7 Single Page Application (SPA)
        ├── package.json                       # Dashboard dependencies (React 19, React Router 7, Firebase JS SDK 12)
        ├── package-lock.json                  # Frontend lockfile
        ├── vite.config.js                     # Vite build configuration with React plugin
        ├── eslint.config.js                   # ESLint 9 flat configuration with React hooks and refresh rules
        ├── index.html                         # HTML5 shell entrypoint with viewport configurations
        ├── README.md                          # Dashboard-specific setup and developer guidelines
        ├── public/                            # Static public web assets
        │   └── vite.svg                       # Vite logo icon
        ├── dist/                              # Compiled, minified production assets generated by vite build
        │   ├── index.html                     # Bundled production HTML shell
        │   ├── vite.svg                       # Production asset
        │   └── assets/                        # Fingerprinted JS/CSS bundles
        │       ├── index-B0FmsJYB.js          # Minified application logic bundle
        │       └── index-iKc3qWK1.css         # Minified production stylesheet
        └── src/                               # Application source code
            ├── main.jsx                       # Application bootstrapping and React DOM root rendering
            ├── App.jsx                        # React Router 7 declarative routing and route protection wrapping
            ├── App.css                        # Root layout styles
            ├── index.css                      # Global design system: Inter typography, color tokens, form styling
            ├── firebase.js                    # Client-side Firebase App, Auth, and Firestore initialization
            ├── assets/                        # Static UI graphic assets
            │   └── react.svg                  # React framework logo
            ├── lib/                           # Core domain logic, state utilities, and test suites
            │   ├── data.js                    # Timestamp parsing, override resolution, stale detection, RBAC scoping
            │   ├── data.test.js               # Domain unit test suite (stale status, timestamp types, role bounds)
            │   ├── live.js                    # Firestore dynamic reactive snapshot listener factory
            │   └── session.jsx                # Auth lifecycle context provider and profile scope validator
            └── pages/                         # Route-level visual screen components
                ├── Login.jsx                  # Enterprise authentication screen with credential validation
                ├── Dashboard.jsx              # Multi-boiler grid overview with real-time status indicators
                └── BoilerDetail.jsx           # Single-boiler deep telemetry inspector & sensor gauge panel
```

---

## 3. Granular File & Component Breakdown

### 3.1 Hardware & Firmware Stack (`Boiler Dash HW component and code/`)

#### 1. `arduinoesp32.ino`
- **Language / Framework**: C++ / Arduino Core for ESP32.
- **Key Responsibilities**:
  - Establishes 802.11 b/g/n Wi-Fi connectivity to the local industrial or testing WLAN (`ssid = "Ak32"`).
  - Initializes `WiFiClientSecure` with non-blocking TLS encryption targeting HiveMQ Cloud broker (`094819d2e9f64c24aad18cf71f8fbdc6.s1.eu.hivemq.cloud:8883`).
  - Configures `PubSubClient` with MQTT client credentials (`Johnny` / `Johnny123456`).
  - Implements an automated reconnection state machine in `reconnect()` to ensure resilience against Wi-Fi drops or socket timeouts.
  - Generates telemetry via simulated physical drift:
    - Temperature: initial $180.0^\circ\text{C} + \text{random}(-5, 5) \times 0.1$.
    - Pressure: initial $6.0\,\text{bar} + \text{random}(-3, 3) \times 0.1$.
    - Flow: initial $10.0\,\text{L/min} + \text{random}(-4, 4) \times 0.1$.
  - Constructs a standardized JSON payload string containing geographical and industrial identifiers (`state`, `district`, `company`, `boiler_id`), numerical readings, and an operational timestamp (`millis()`).
  - Publishes telemetry packets every 5,000 milliseconds to the designated MQTT topic.

#### 2. `Certificates.h`
- **Content**: Contains the PEM-encoded X.509 Root Certificate for **Amazon Root CA 1** (`-----BEGIN CERTIFICATE----- ... -----END CERTIFICATE-----`).
- **Cryptographic Purpose**: Serves as the Trust Anchor for the ESP32 `WiFiClientSecure` stack to validate the digital certificate presented by the HiveMQ Cloud broker during TLS handshake, preventing Man-In-The-Middle (MITM) attacks on the telemetry link.

#### 3. `dashboard.html`
- **Technology**: Pure HTML5, Vanilla JavaScript, embedded CSS, and `mqtt.min.js` (loaded via CDN).
- **Functionality**:
  - Acts as a lightweight, zero-dependency engineering diagnostic interface.
  - Connects directly to HiveMQ Cloud over secure WebSockets (`wss://...:8884/mqtt`).
  - Subscribes to wildcard topic `boiler/#`.
  - Implements a 10-second client-side watchdog timer: if no MQTT packet arrives within $10,000\,\text{ms}$, updates UI status to `"DEVICE OFFLINE"`.
  - Evaluates immediate hazard thresholds:
    - `DANGER`: Pressure $> 8\,\text{bar}$ OR Temperature $> 220^\circ\text{C}$.
    - `WARNING`: Pressure $> 6\,\text{bar}$ OR Temperature $> 200^\circ\text{C}$.
    - `NORMAL`: Nominal operational parameters.

---

### 3.2 Ingestion Bridge Microservice (`Boiler Web 1.0/boiler-mqtt-bridge/`)

#### 1. `index.js`
- **Runtime**: Node.js 22 LTS microservice daemon.
- **Dependencies**: `mqtt`, `firebase-admin`, `./payload`, `./firebase`.
- **Architecture**:
  - Connects to HiveMQ Cloud via mutual TLS (`rejectUnauthorized: true`, reconnect period $5,000\,\text{ms}$).
  - Subscribes with Quality of Service 1 (QoS 1) to `boiler/+/telemetry` and `boiler/+/override`.
  - Implements `client.handleMessage`:
    - Normalizes topic and payload via `./payload.js`. Rejects malformed or unregistered packets without crashing.
    - Validates boiler registration by performing an atomic indexed Firestore query on collection `boilers` matching `boiler_id`.
    - Enriches the document with authorized organization metadata (`company`, `district`, `state`, `address`).
    - Appends a high-precision `admin.firestore.FieldValue.serverTimestamp()`.
    - Persists into Firestore collections `telemetry` or `override_logs`.
    - Executes a 3-stage bounded retry with progressive backoff ($1,000\,\text{ms}, 2,000\,\text{ms}$) on failure.
    - Acknowledges the QoS 1 packet (`done()`) only after database commit completes.
  - Implements graceful process teardown on `SIGINT` and `SIGTERM` signals, terminating MQTT sessions and flushing active Firestore writes.

#### 2. `payload.js`
- **Module Type**: Pure functional validation and transformation utility.
- **Key Functions**:
  - `booleanValue(value)`: Strictly coerces truthy (`true`, `1`, `'1'`, `'true'`) and falsy (`false`, `0`, `'0'`, `'false'`) values into native booleans. Throws on ambiguous values.
  - `timestamp(value, now)`: Handles epoch seconds, epoch milliseconds, and ISO-8601 strings, converting them to UTC milliseconds. Enforces sanity boundaries (rejects zero, negative, or timestamps $> 5\,\text{minutes}$ in the future).
  - `normalizeMessage(topic, data, now)`:
    - Validates topic syntax against regular expression `^boiler/([^/]+)/(telemetry|override)$`.
    - Enforces topic boiler ID equality with payload `boiler_id`.
    - Strictly checks numeric types for `temperature_c`, `pressure_bar`, `flow_lpm`, and `tds_ppm`.
    - Validates `device_status` as either `'online'` or `'offline'`.
    - Returns standardized Firestore document payload and target collection designation.

#### 3. `payload.test.js`
- **Test Framework**: Native Node.js test runner (`node:test`, `node:assert/strict`).
- **Test Coverage**:
  - Extraction of boiler ID from topic strings.
  - Correct normalization of epoch seconds, milliseconds, and ISO timestamps.
  - Rejection of invalid payloads (empty objects, null, strings in numeric fields, malformed topics).
  - Validation of boolean coercion for safety overrides.

#### 4. `firebase.js`
- **Role**: Backend Firebase Admin SDK initialization singleton.
- **Security**: Loads environment configuration from `.env` via `process.loadEnvFile()`. Binds Google Cloud Service Account credentials from the JSON keyfile specified in `GOOGLE_APPLICATION_CREDENTIALS`.

#### 5. `create_users.js`
- **CLI Utility**: Administrative provisioning script for setting up enterprise users.
- **Input Parameters**: Environment variables `USER_EMAIL`, `USER_PASSWORD`, `USER_NAME`, `USER_ROLE`, `USER_COMPANY`, `USER_DISTRICT`.
- **Execution Flow**:
  - Validates role criteria (`admin`, `owner`, `inspector`). Requires `company` for owners, `district` for inspectors.
  - Creates or retrieves Firebase Authentication account (enforcing 12+ character password policy).
  - Upserts Firestore document in `users/{uid}` with assigned organizational metadata.

#### 6. `migrate_profiles.js`
- **CLI Utility**: Data migration and identity reconciliation script.
- **Purpose**: Migrates legacy user documents to canonical documents keyed by the Firebase Auth UID.
- **Safety**: Supports read-only dry-run mode by default; applies atomic batch updates only when `--apply` flag is passed. Refuses migration if conflicting role assignments are detected.

#### 7. `check_db.js`
- **CLI Diagnostic**: Inspects Cloud Firestore database connectivity and outputs the first 5 records of collections `users`, `boilers`, `telemetry`, and `override_logs`.

---

### 3.3 Production Web Dashboard (`Boiler Web 1.0/boiler-dashboard/`)

#### 1. `src/App.jsx`
- **Framework**: React 19 + React Router 7.
- **Architecture**: Defines declarative URL routing:
  - `/`: Public enterprise `Login` page.
  - `/dashboard`: Protected multi-boiler grid view wrapped by `<Session />`.
  - `/boiler/:id`: Protected single-boiler deep telemetry inspection view.
  - `*`: Fallback wildcard redirecting to `/dashboard`.

#### 2. `src/lib/session.jsx`
- **Role**: Secure route-guard and session manager.
- **Execution Lifecycle**:
  - Subscribes to Firebase Auth via `onAuthStateChanged`.
  - Fetches user profile document `users/{user.uid}` from Firestore.
  - Invokes `scopeFor(profile)` to compute data visibility constraints based on role.
  - Renders child routes via `<Outlet context={session} />` or redirects unauthenticated traffic to `/`.

#### 3. `src/lib/data.js`
- **Core Domain Logic**:
  - `timeMillis(value)`: Universal timestamp parser supporting Firestore Timestamps, integer epoch seconds, epoch milliseconds, and date strings.
  - `formatTime(data)`: Produces localized, human-readable date-time strings.
  - `overrideValue(telemetry, event)`: Implements conflict resolution between continuous telemetry override flags and discrete override log events based on newest timestamp.
  - `status(telemetry, event, now)`: Computes high-level operational state:
    - `"No Data"` (`#94a3b8`): Null telemetry.
    - `"Offline"` (`#ef4444`): `device_status != 'online'`.
    - `"Stale Data"` (`#f59e0b`): Last received packet $> 120,000\,\text{ms}$ old.
    - `"Override Active"` (`#f59e0b`): Manual safety override enabled.
    - `"Online"` (`#10b981`): Active, fresh, healthy telemetry stream.
  - `scopeFor(profile)`: Computes Firestore query filter tuples (`['company', profile.company]` or `['district', profile.district]`, or `null` for administrators).

#### 4. `src/lib/data.test.js`
- **Test Framework**: Node.js test runner validating client domain logic.
- **Coverage**: Timestamp normalization, override conflict resolution, stale data timeout thresholds (120 seconds), and role boundary protection.

#### 5. `src/lib/live.js`
- **Reactive Streaming**: Wraps Firestore `onSnapshot` queries with compound filtering (`boiler_id == id`, `orderBy('timestamp', 'desc')`, `limit(1)`). Returns an unsubscription callback to prevent memory leaks.

#### 6. `src/pages/Dashboard.jsx`
- **User Interface**: Multi-boiler operational overview.
- **Features**:
  - User identity badge displaying name, role, company, and district.
  - Reactive query listener dynamically attaching snapshot listeners across all assigned boilers.
  - Live color-coded status indicator lamps with CSS drop-shadow glow effects.
  - Real-time display of critical parameters: Temperature (°C), Pressure (bar), Flow Rate (L/min), and TDS (ppm).
  - Keyboard accessible navigation (`Enter` key or click to view details).

#### 7. `src/pages/BoilerDetail.jsx`
- **User Interface**: Dedicated single-boiler diagnostic center.
- **Features**:
  - Route parameter binding (`/boiler/:id`).
  - Role-scoped authorization check ensuring the requested boiler matches the authenticated user's assigned scope.
  - Detailed metadata card: Company, District, State, Physical Installation Address.
  - Live metric gauge panels for all four primary sensors.
  - Override state indicator (ON / OFF) and latest packet timestamp.

#### 8. `src/pages/Login.jsx`
- **User Interface**: Minimalist dark-themed enterprise authentication screen.
- **Security**: Controlled form inputs, disabled states during submission, comprehensive error handling for rate-limiting, network disconnection, and bad credentials.

---

### 3.4 Cloud Database & Configuration Artifacts

#### 1. `firestore.rules`
- **Security Paradigm**: Declarative Zero-Trust access control.
- **Key Directives**:
  - Client writes are completely prohibited across all collections (`write: false`). Only the Node.js backend bridge using Firebase Admin SDK possesses write credentials.
  - Authenticated users can only read their own profile document: `users/{uid}`.
  - Access to `boilers`, `telemetry`, and `override_logs` is governed by the `allowed()` helper function:
    - Administrators: Global read permissions.
    - Factory Owners: Read access permitted only if `boiler.company == profile.company`.
    - Safety Inspectors: Read access permitted only if `boiler.district == profile.district`.

#### 2. `firestore.indexes.json`
- **Database Optimization**: Declares composite B-tree indexes for Cloud Firestore:
  - Collection Group `telemetry`: `boiler_id ASC, timestamp DESC`.
  - Collection Group `override_logs`: `boiler_id ASC, timestamp DESC`.
- **Performance Impact**: Enables the web dashboard to retrieve the latest telemetry document in $\mathcal{O}(\log N)$ time, avoiding full table scans across millions of historical readings.

#### 3. `firebase.json`
- **Hosting Specification**: Configures Single Page Application (SPA) URL rewrites mapping all incoming requests (`"source": "**"`) to `/index.html` within `boiler-dashboard/dist`.

---

## 4. Hardware Subsystems & Circuit Specifications

### 4.1 Physical Sensing Transducers & Pin Allocations

| Component | Sensor Model | Operating Principle | Measurement Range | Output Signal | ESP32 Pin Allocation | Operating Voltage |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Microcontroller** | ESP32-WROOM-32D | Dual-Core 32-bit Xtensa LX6 | 240 MHz, 520 KB SRAM | Wi-Fi / Bluetooth / GPIO | N/A (Master MCU) | 3.3V DC |
| **Temperature Sensor** | DS18B20 / RTD Probe | Silicon Bandgap / Platinum Thin Film | $-55^\circ\text{C} \text{ to } +125^\circ\text{C}$ (Up to $400^\circ\text{C}$ w/ RTD) | Dallas 1-Wire Digital / Analog | GPIO 4 (1-Wire with $4.7\,\text{k}\Omega$ pullup) | 3.3V – 5.0V |
| **Pressure Transducer** | Piezoresistive Transmitter | Silicon piezoresistive diaphragm | $0 \text{ to } 10.0 / 16.0\,\text{bar}$ | $0.5\text{V} – 4.5\text{V}$ Analog Linear | GPIO 34 (ADC1 Channel 6) | 5.0V DC |
| **Water Flow Sensor** | YF-S201 Turbine | Hall-Effect Pulse Generation | $1.0 \text{ to } 30.0\,\text{L/min}$ | Digital Pulse Train ($f = 7.5 \times Q$) | GPIO 18 (Hardware Interrupt) | 5.0V DC |
| **TDS Sensor** | Analog Electrical Conductivity | Dual-electrode AC excitation | $0 \text{ to } 1,000\,\text{ppm}$ | $0.0\text{V} – 2.3\text{V}$ Analog Linear | GPIO 35 (ADC1 Channel 7) | 3.3V – 5.0V |
| **Power Converter** | LM2596 / Buck Module | High-frequency DC-DC switching | Step-down $12\text{V}/24\text{V} \to 5\text{V}$ | $5.0\text{V} \pm 1\%$, up to $3\text{A}$ | VIN & GND Rail | $12\text{V} – 24\text{V}$ Input |

---

### 4.2 Sensor Signal Conditioning & Formulations

#### 1. Temperature Calculation (Analog RTD / 1-Wire DS18B20)
For digital DS18B20 sensors, temperature is read directly via the 1-Wire protocol with 12-bit precision ($0.0625^\circ\text{C}$ resolution):
$$T_{\text{DS18B20}} = \text{RawWord} \times 0.0625$$
For high-temperature industrial RTDs (PT100) using the Callendar-Van Dusen equation:
$$R(T) = R_0 \left(1 + A T + B T^2\right)$$
where $R_0 = 100\,\Omega$, $A = 3.9083 \times 10^{-3}\,^\circ\text{C}^{-1}$, and $B = -5.775 \times 10^{-7}\,^\circ\text{C}^{-2}$.

#### 2. Pressure Transducer Linear Transfer Function
The piezoresistive transducer provides a linear voltage output between $0.5\,\text{V}$ (0 bar gauge) and $4.5\,\text{V}$ ($P_{\max} = 10\,\text{bar}$). After scaling through an input voltage divider to match the ESP32 $0 - 3.3\,\text{V}$ ADC input range:
$$P(\text{bar}) = \left(\frac{V_{\text{sensor}} - 0.5}{4.0}\right) \times P_{\max}$$

#### 3. Volumetric Flow Rate Calculation
The Hall-effect turbine rotor outputs 450 electrical pulses per liter of fluid passed through the chamber:
$$Q\,(\text{L/min}) = \frac{f_{\text{pulse}}\,(\text{Hz})}{7.5}$$

#### 4. Total Dissolved Solids (TDS) & Water Hardness
Boiler water conductivity directly correlates with mineral concentration. Unchecked dissolved minerals cause scale accumulation on heat-exchange surfaces, drastically reducing thermal efficiency and inducing localized hot-spots:
$$V_{\text{corrected}} = \frac{V_{\text{raw}}}{1.0 + 0.02 \times (T - 25.0)}$$
$$\text{TDS}\,(\text{ppm}) = \left(133.42 \times V_{\text{corrected}}^3 - 255.86 \times V_{\text{corrected}}^2 + 857.39 \times V_{\text{corrected}}\right) \times 0.5$$

---

## 5. End-to-End System Architecture & Data Flow

```text
 ┌────────────────────────────────────────────────────────────────────────┐
 │                        PHYSICAL SENSING LAYER                          │
 │  ┌─────────────────┐  ┌─────────────────┐  ┌────────────────────────┐  │
 │  │ Temperature     │  │ Pressure        │  │ Water Flow & TDS       │  │
 │  │ Probe (DS18B20) │  │ Transducer      │  │ Sensors (YF-S201)      │  │
 │  └────────┬────────┘  └────────┬────────┘  └───────────┬────────────┘  │
 └───────────┼────────────────────┼───────────────────────┼───────────────┘
             └────────────────────┼───────────────────────┘
                                  ▼
 ┌────────────────────────────────────────────────────────────────────────┐
 │                      EMBEDDED EDGE CONTROLLER                          │
 │                     ESP32 Dual-Core 240MHz MCU                         │
 │   - Analog-to-Digital Conversion (ADC) & Interrupt Counting            │
 │   - Dynamic Sensor Sampling Loop (5000ms Interval)                     │
 │   - JSON Telemetry Serialization                                       │
 │   - WiFiClientSecure TLS 1.2 Socket (Port 8883)                        │
 └────────────────────────────────┬───────────────────────────────────────┘
                                  │  MQTTS (TLS 8883)
                                  ▼
 ┌────────────────────────────────────────────────────────────────────────┐
 │                        CLOUD BROKER LAYER                              │
 │                      HiveMQ Cloud Enterprise                           │
 │   - TLS Mutual Authentication via Amazon Root CA 1                     │
 │   - QoS 1 (At Least Once Delivery) Message Routing                     │
 │   - Topics: boiler/{boiler_id}/telemetry & boiler/{boiler_id}/override │
 └────────────────────────────────┬───────────────────────────────────────┘
                                  │  QoS 1 Ingestion Stream
                                  ▼
 ┌────────────────────────────────────────────────────────────────────────┐
 │                   NODE.JS INGESTION BRIDGE DAEMON                      │
 │   - Pure Functional Schema Validation & Sanitization (payload.js)      │
 │   - Boiler Registry Verification (boilers collection query)            │
 │   - Metadata Enrichment (company, district, state, address)            │
 │   - 3-Stage Bounded Retry Logic with Exponential Backoff               │
 └────────────────────────────────┬───────────────────────────────────────┘
                                  │  Firebase Admin SDK Write
                                  ▼
 ┌────────────────────────────────────────────────────────────────────────┐
 │                     GOOGLE CLOUD FIRESTORE                             │
 │   - Collections: users, boilers, telemetry, override_logs              │
 │   - Composite Indexes: boiler_id ASC + timestamp DESC                  │
 │   - Zero-Trust Security Rules: Strict Role-Based Read Scopes           │
 └────────────────────────────────┬───────────────────────────────────────┘
                                  │  Reactive onSnapshot Realtime Sync
                                  ▼
 ┌────────────────────────────────────────────────────────────────────────┐
 │                  ENTERPRISE WEB DASHBOARD (REACT 19)                   │
 │   - Role-Scoped Authorization (Inspector, Owner, Administrator)        │
 │   - Stale Data Detection Engine (120-second Watchdog)                  │
 │   - Multi-Boiler Realtime Status Grid & Deep Telemetry Viewer          │
 └────────────────────────────────────────────────────────────────────────┘
```

---

## 6. MQTT Messaging Protocols & Schema Definitions

### 6.1 Telemetry Contract (`boiler/{boiler_id}/telemetry`)

#### Telemetry Payload Schema
```json
{
  "boiler_id": "B01",
  "temperature_c": 182.45,
  "pressure_bar": 6.32,
  "flow_lpm": 10.15,
  "tds_ppm": 340.50,
  "device_status": "online",
  "override": false,
  "timestamp": 1780000000000
}
```

#### Field Specifications:
- `boiler_id` (*string, required*): Alphanumeric identifier of the physical boiler unit. Must strictly match the wildcard topic parameter.
- `temperature_c` (*number, required*): Real-time temperature measurement in degrees Celsius.
- `pressure_bar` (*number, required*): Real-time gauge pressure in bar.
- `flow_lpm` (*number, required*): Coolant or feed-water volumetric flow rate in Liters per minute.
- `tds_ppm` (*number, optional*): Total Dissolved Solids in parts per million.
- `device_status` (*string, required*): Edge hardware health status; strictly `'online'` or `'offline'`.
- `override` (*boolean, optional*): Hardware safety valve or manual bypass status (`true` = Active, `false` = Inactive).
- `timestamp` (*integer / ISO string, optional*): Timestamp of acquisition in epoch milliseconds. Automatically assigned receive time if omitted.

---

### 6.2 Override Contract (`boiler/{boiler_id}/override`)

#### Override Payload Schema
```json
{
  "boiler_id": "B01",
  "override": true,
  "source": "hardware_manual_switch",
  "timestamp": 1780000005000
}
```

#### Field Specifications:
- `boiler_id` (*string, required*): Target boiler identifier matching topic.
- `override` (*boolean / numeric string, required*): Explicit safety override state (`true`, `false`, `1`, `0`).
- `source` (*string, optional*): Provenance of override trigger (e.g. `'hardware_manual_switch'`, `'dashboard_operator'`, `'emergency_scram'`). Defaults to `'hardware'`.
- `timestamp` (*integer / ISO string, optional*): Event occurrence timestamp.

---

## 7. Cloud Firestore Database Architecture & Security Model

### 7.1 Entity Relationship Model

```text
 ┌──────────────────────────────────────────────────────────────┐
 │                      users/{uid}                             │
 ├──────────────────────────────────────────────────────────────┤
 │ uid: string (Auth UID)                                       │
 │ email: string                                                │
 │ name: string                                                 │
 │ role: "admin" | "owner" | "inspector"                       │
 │ company: string (mandatory for owner)                        │
 │ district: string (mandatory for inspector)                   │
 └──────────────────────────────────────────────────────────────┘
                                │
                                │ Scoped Read Isolation
                                ▼
 ┌──────────────────────────────────────────────────────────────┐
 │                     boilers/{boiler_id}                      │
 ├──────────────────────────────────────────────────────────────┤
 │ boiler_id: string (Document Key, e.g. "B01")                 │
 │ company: string (e.g. "TataSteel")                           │
 │ district: string (e.g. "Chennai")                            │
 │ state: string (e.g. "TN")                                    │
 │ address: string (Physical facility address)                  │
 └──────────────────────────────────────────────────────────────┘
          │                                            │
          │ 1 : N                                      │ 1 : N
          ▼                                            ▼
 ┌──────────────────────────────┐     ┌──────────────────────────────┐
 │       telemetry/{docId}      │     │    override_logs/{docId}     │
 ├──────────────────────────────┤     ├──────────────────────────────┤
 │ boiler_id: string            │     │ boiler_id: string            │
 │ company: string              │     │ company: string              │
 │ district: string             │     │ district: string             │
 │ state: string                │     │ state: string                │
 │ address: string              │     │ address: string              │
 │ temperature_c: number        │     │ override: boolean            │
 │ pressure_bar: number         │     │ source: string               │
 │ flow_lpm: number             │     │ timestamp: number (ms)       │
 │ tds_ppm: number              │     │ created_at: ServerTimestamp  │
 │ device_status: string        │     │ created_at_ms: number        │
 │ override: boolean            │     └──────────────────────────────┘
 │ timestamp: number (ms)       │
 │ created_at: ServerTimestamp  │
 │ created_at_ms: number        │
 └──────────────────────────────┘
```

---

### 7.2 Zero-Trust Security Policy Matrix

| User Role | Profile Requirements | Access Scope: `users` | Access Scope: `boilers` | Access Scope: `telemetry` | Access Scope: `override_logs` | Write Access |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Central Admin** | `role == 'admin'` | Read self profile (`uid == auth.uid`) | Full Unrestricted Read across all registered boilers | Full Unrestricted Read across all telemetry records | Full Unrestricted Read across all override logs | Denied (Read-Only) |
| **Factory Owner** | `role == 'owner'`, `company != ''` | Read self profile (`uid == auth.uid`) | Read restricted to `boiler.company == profile.company` | Read restricted to telemetry where boiler company matches | Read restricted to override logs where boiler company matches | Denied (Read-Only) |
| **Safety Inspector**| `role == 'inspector'`, `district != ''` | Read self profile (`uid == auth.uid`) | Read restricted to `boiler.district == profile.district` | Read restricted to telemetry where boiler district matches | Read restricted to override logs where boiler district matches | Denied (Read-Only) |
| **Unauthenticated** | None | Denied | Denied | Denied | Denied | Denied |
| **Node.js Bridge** | Google Service Account | Full Read / Write | Full Read (Verification) | Full Append / Write | Full Append / Write | Granted (Admin SDK) |

---

## 8. Safety Evaluation State Machine & Operational Algorithms

### 8.1 Real-Time Hazard Classification

In boiler thermodynamics, thermal expansion and steam vapor pressure are bound by the saturated steam curve (Clausius-Clapeyron relation). When pressure or temperature crosses designated engineering thresholds, safety states transition dynamically:

$$\text{Operational State} = \begin{cases}
\mathbf{DANGER} & \text{if } P > 8.0\,\text{bar} \quad \lor \quad T > 220.0^\circ\text{C} \\
\mathbf{WARNING} & \text{if } P > 6.0\,\text{bar} \quad \lor \quad T > 200.0^\circ\text{C} \\
\mathbf{NORMAL} & \text{otherwise}
\end{cases}$$

### 8.2 Watchdog Stale Data Detection Algorithm
To prevent operators from acting upon frozen or outdated telemetry caused by network partitions or hardware failure, the system computes data freshness dynamically:
$$\Delta t = t_{\text{current}} - \max(t_{\text{created\_at\_ms}},\, t_{\text{timestamp}})$$
$$\text{Liveness Status} = \begin{cases}
\text{No Data} & \text{if } \text{telemetry} = \text{null} \\
\text{Offline} & \text{if } \text{device\_status} \neq \text{'online'} \\
\text{Stale Data} & \text{if } \Delta t > 120,000\,\text{ms} \\
\text{Override Active} & \text{if } \text{override} = \text{true} \\
\text{Online} & \text{if } \Delta t \le 120,000\,\text{ms}
\end{cases}$$

---

## 9. Testing & Verification Summary

The codebase incorporates multi-tier automated test suites validating data integrity, protocol conformance, and security rules:
- **`payload.test.js`**: 4 comprehensive test suites covering:
  - Boiler ID topic extraction and missing timestamp imputation.
  - Consistent epoch seconds, milliseconds, and ISO-8601 parsing.
  - Strict payload rejection on malformed numeric strings, null objects, or schema violations.
  - Preservation of explicit boolean states and numeric overrides.
- **`data.test.js`**: 4 comprehensive test suites covering:
  - Universal timestamp decoding across Firestore objects, seconds, and dates.
  - Dynamic override timestamp ordering (newer telemetry clears older overrides).
  - Stale status threshold validation ($120\,\text{seconds}$).
  - Role-based scoping security bounds.
- **Verification Execution**: Both suites run via `npm test` with 100% pass rates.

---

## 10. Operational & Deployment Guide

### Local Development Setup:
```bash
# 1. Install workspace dependencies
cd "Boiler Web 1.0"
npm --prefix boiler-dashboard install
npm --prefix boiler-mqtt-bridge install

# 2. Configure Bridge Environment
cp boiler-mqtt-bridge/.env.example boiler-mqtt-bridge/.env
# Edit boiler-mqtt-bridge/.env with HiveMQ and Service Account credentials

# 3. Start Frontend Dashboard (Port 5173)
npm run dev

# 4. Start Ingestion Bridge Microservice (Separate terminal)
npm run bridge

# 5. Execute Linters and Unit Test Suites
npm run lint
npm test

# 6. Compile Production Frontend Distribution
npm run build
```

---
*End of Master Technical Specification — Smart Boiler Monitoring and Safety Management System.*
