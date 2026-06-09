import streamlit as st
import pandas as pd
import os
from datetime import datetime, timedelta
import time
import subprocess

st.set_page_config(page_title="Grand Hotel Management", page_icon="🏨", layout="wide")
st.markdown("""
    <style>
    .stApp {
        background: linear-gradient(135deg, #06101E 0%, #0B1E36 50%, #122D52 100%);
        color: #E2E8F0;
    }
    div[data-testid="stForm"], .stAlert, div[data-testid="stExpander"] {
        background: rgba(255, 255, 255, 0.04) !important;
        backdrop-filter: blur(12px);
        -webkit-backdrop-filter: blur(12px);
        border: 1px solid rgba(255, 255, 255, 0.15) !important;
        border-radius: 16px !important;
        box-shadow: 0 8px 32px 0 rgba(0, 26, 51, 0.5), inset 0 0 15px rgba(255, 255, 255, 0.05) !important;
    }
    
    div[data-testid="stForm"]:hover {
        border-color: rgba(0, 191, 255, 0.4) !important;
        box-shadow: 0 8px 32px 0 rgba(0, 191, 255, 0.2) !important;
        transition: all 0.3s ease-in-out;
    }
    
    div[data-testid="stCheckbox"] p {
        color: #E2E8F0 !important;
        font-size: 16px;
    }

    .stTabs [data-baseweb="tab"] {
        color: #94A3B8 !important;
        font-weight: bold;
    }
    .stTabs [aria-selected="true"] {
        color: #00BFFF !important;
        border-bottom-color: #00BFFF !important;
    }

    button[kind="primary"] {
        background: linear-gradient(45deg, #00BFFF, #1E40AF) !important;
        color: white !important;
        border: none !important;
        box-shadow: 0 4px 15px rgba(0, 191, 255, 0.4) !important;
        font-weight: bold !important;
        border-radius: 8px !important;
    }

    .done-banner {
        background: linear-gradient(90deg, #052E16 0%, #14532D 100%) !important;
        border: 2px solid #22C55E !important;
        padding: 20px;
        border-radius: 12px;
        text-align: center;
        box-shadow: 0 0 20px rgba(34, 197, 94, 0.3);
        margin-bottom: 20px;
    }
    </style>
""", unsafe_allow_html=True)

def run_backend_command(args):
    try:
        result = subprocess.run(["./hotel_backend.exe"] + args, capture_output=True, text=True, check=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return f"ERROR: Execution failed -> {e.stderr}"
    except FileNotFoundError:
        return "ERROR: hotel_backend.exe not found. Please compile C++ first."

def calculate_days(start_str, end_str):
    try:
        start_date = datetime.strptime(start_str, "%d-%m-%Y")
        end_date = datetime.strptime(end_str, "%d-%m-%Y")
        days = (end_date - start_date).days
        return days if days > 0 else 0
    except:
        return 0

def load_rooms():
    rooms = []
    if os.path.exists("rooms.txt"):
        with open("rooms.txt", "r", encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    parts = line.strip().split(',')
                    rooms.append({"RoomNum": int(parts[0]), "RoomType": parts[1], "RoomStatus": parts[2], "RoomPrice": float(parts[3])})
    else:
        for i in range(1, 301):
            if i <= 100: rooms.append({"RoomNum": i, "RoomType": "Single", "RoomStatus": "Available", "RoomPrice": 500.0})
            elif i <= 200: rooms.append({"RoomNum": i, "RoomType": "Double", "RoomStatus": "Available", "RoomPrice": 800.0})
            else: rooms.append({"RoomNum": i, "RoomType": "Suite", "RoomStatus": "Available", "RoomPrice": 1500.0})
        save_rooms(rooms)
    return rooms

def save_rooms(rooms):
    with open("rooms.txt", "w", encoding="utf-8") as f:
        for r in rooms:
            f.write(f"{r['RoomNum']},{r['RoomType']},{r['RoomStatus']},{r['RoomPrice']}\n")

def load_users():
    users = []
    if os.path.exists("users.txt"):
        with open("users.txt", "r", encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    parts = line.strip().split(',')
                    if parts[3] == "admin":
                        users.append({"username": parts[0], "id": int(parts[1]), "password": parts[2], "usertype": parts[3]})
                    else:
                        ec = float(parts[4]) if len(parts) > 4 else 0.0
                        users.append({"username": parts[0], "id": int(parts[1]), "password": parts[2], "usertype": parts[3], "extraCharges": ec})
    else:
        users = [
            {"username": "merna", "id": 1, "password": "123", "usertype": "admin"},
            {"username": "malak", "id": 2, "password": "345", "usertype": "admin"},
            {"username": "jannah", "id": 3, "password": "678", "usertype": "admin"}
        ]
        save_users(users)
    return users

def save_users(users):
    with open("users.txt", "w", encoding="utf-8") as f:
        for u in users:
            if u['usertype'] == "admin":
                f.write(f"{u['username']},{u['id']},{u['password']},{u['usertype']}\n")
            else:
                f.write(f"{u['username']},{u['id']},{u['password']},{u['usertype']},{u.get('extraCharges', 0.0)}\n")

def load_reservations():
    reservations = []
    if os.path.exists("reservations.txt"):
        with open("reservations.txt", "r", encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    p = line.strip().split(',')
                    reservations.append({
                        "ResID": int(p[0]), "GuestID": int(p[1]), "RoomNum": int(p[2]), 
                        "CheckIn": p[3], "CheckOut": p[4], "Duration": int(p[5]),
                        "Breakfast": int(p[6]), "Lunch": int(p[7]), "Dinner": int(p[8])
                    })
    return reservations

def save_reservations(reservations):
    with open("reservations.txt", "w", encoding="utf-8") as f:
        for r in reservations:
            f.write(f"{r['ResID']},{r['GuestID']},{r['RoomNum']},{r['CheckIn']},{r['CheckOut']},{r['Duration']},{r['Breakfast']},{r['Lunch']},{r['Dinner']}\n")

def load_events():
    events = []
    if os.path.exists("events.txt"):
        with open("events.txt", "r", encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    p = line.strip().split(',')
                    events.append({
                        "EventID": int(p[0]), "GuestID": int(p[1]), "Type": p[2], 
                        "Singer": p[3], "Date": p[4], "Price": float(p[5])
                    })
    return events

def save_events(events):
    with open("events.txt", "w", encoding="utf-8") as f:
        for e in events:
            f.write(f"{e['EventID']},{e['GuestID']},{e['Type']},{e['Singer']},{e['Date']},{e['Price']}\n")

# تهيئة الجلسة
if 'logged_in' not in st.session_state:
    st.session_state.logged_in = False
    st.session_state.user_info = {}
if 'booking_success_msg' not in st.session_state:
    st.session_state.booking_success_msg = ""

rooms_db = load_rooms()
users_db = load_users()
res_db = load_reservations()
events_db = load_events()

if not st.session_state.logged_in:
    col1, col2, col3 = st.columns([1, 1.8, 1])
    with col2:
        st.markdown("<br><h1 style='text-align: center; color: #00BFFF; text-shadow: 0 0 10px rgba(0,191,255,0.5);'>🏨 Grand Hotel System</h1>", unsafe_allow_html=True)
        st.markdown("<p style='text-align: center; color: #94A3B8;'>Luxury Stay & Smart Management</p>", unsafe_allow_html=True)
        
        tab1, tab2 = st.tabs(["🔒 Secure Login", "📝 Create New Account"])
        
        with tab1:
            with st.form("login"):
                u_name = st.text_input("Username")
                u_pass = st.text_input("Password", type="password")
                if st.form_submit_button("Login to Dashboard", use_container_width=True, type="primary"):
                    clean_u_name = u_name.strip()
                    clean_u_pass = u_pass.strip()
                    
                    res = run_backend_command(["LOGIN", clean_u_name, clean_u_pass])
                    
                    if res.startswith("SUCCESS"):
                        user_data = res.replace("SUCCESS:", "").split(",")
                        st.session_state.logged_in = True
           
                        extra_c = float(user_data[3]) if len(user_data) > 3 else 0.0
                        st.session_state.user_info = {
                            "username": user_data[0],
                            "id": int(user_data[1]),
                            "password": clean_u_pass,
                            "usertype": user_data[2],
                            "extraCharges": extra_c
                        }
                        st.rerun()
                    else:
                        st.error("Invalid Username or Password via Backend Server!")
        
        with tab2:
            with st.form("register"):
                new_u = st.text_input("New Username")
                new_p = st.text_input("New Password", type="password")
                if st.form_submit_button("Register Account", use_container_width=True):
                    clean_u = new_u.strip()
                    clean_p = new_p.strip()
                    
                    if clean_u and clean_p:
                        if "," in clean_u or "," in clean_p:
                            st.error("Commas (,) are not allowed.")
                        else:
                            res = run_backend_command(["REGISTER", clean_u, clean_p])
                            if res.startswith("SUCCESS"):
                                st.success("✅ Registered Successfully via Backend! Switch to Login tab.")
                                users_db = load_users() 
                            else:
                                st.warning(f"⚠️ {res.replace('ERROR:', '')}")
                    else:
                        st.warning("⚠️ Please fill all fields.")

elif st.session_state.user_info['usertype'] == "admin":
    st.sidebar.markdown(f"<h2 style='color:#00BFFF;'>👨‍💼 Manager Desk</h2>", unsafe_allow_html=True)
    st.sidebar.write(f"Active: **{st.session_state.user_info['username']}**")
    if st.sidebar.button("Log Out System", use_container_width=True):
        st.session_state.logged_in = False
        st.rerun()

    st.title("Hotel Administration Panel 📊")
    
    t1, t2 = st.tabs(["🛏️ Master Room Directory", "📝 Override Room Status"])
    
    with t1:
        st.dataframe(pd.DataFrame(rooms_db), use_container_width=True, hide_index=True)
        
    with t2:
        with st.form("update_room"):
            c1, c2 = st.columns(2)
            with c1:
                r_num = st.number_input("Target Room Number", min_value=1, max_value=300)
            with c2:
                r_stat = st.selectbox("Assign New Status", ["Available", "Booked (Unavailable)"])
            
            if st.form_submit_button("Apply Changes", type="primary"):
                for r in rooms_db:
                    if r['RoomNum'] == r_num:
                        r['RoomStatus'] = r_stat
                        save_rooms(rooms_db)
                        st.success(f"Room {r_num} updated to {r_stat} successfully!")
                        st.rerun()

elif st.session_state.user_info['usertype'] == "guest":
    guest = st.session_state.user_info
    
    st.sidebar.markdown(f"<h2 style='color:#00BFFF;'>🏨 Grand Portal</h2>", unsafe_allow_html=True)
    st.sidebar.write(f"Welcome Guest: **{guest['username']}**")
    st.sidebar.write(f"Your Account ID: **#{guest['id']}**")
    if st.sidebar.button("Log Out", use_container_width=True):
        st.session_state.logged_in = False
        st.session_state.booking_success_msg = ""
        st.rerun()

    st.title("Guest Premium Dashboard ")
    if st.session_state.booking_success_msg:
        st.markdown(st.session_state.booking_success_msg, unsafe_allow_html=True)
        if st.button("Clear Notification"):
            st.session_state.booking_success_msg = ""
            st.rerun()

    gt1, gt2, gt3, gt4, gt5 = st.tabs([
        "🛏️ Reserve Room", "📅 My Bookings & Itinerary", "🎉 Events & Galas", "💆 Spa & Room Service", "🧾 Instant Invoice"
    ])

    with gt1:
        st.subheader("Explore & Book Available Rooms")
        available_rooms = [r for r in rooms_db if r['RoomStatus'] == "Available"]
        
        with st.form("book_room"):
            c1, c2, c3 = st.columns(3)
            
            today_str = datetime.now().strftime("%d-%m-%Y")
            tomorrow_str = (datetime.now() + timedelta(days=2)).strftime("%d-%m-%Y")
            
            with c1:
                r_select = st.selectbox("Choose Room Number", [r['RoomNum'] for r in available_rooms])
            with c2:
                in_date = st.text_input("Check-in Date (DD-MM-YYYY)", value=today_str)
            with c3:
                out_date = st.text_input("Check-out Date (DD-MM-YYYY)", value=tomorrow_str)
                
            st.markdown("<p style='color:#00BFFF; font-weight:bold; margin-top:10px;'>🍔 Daily Meal Add-ons</p>", unsafe_allow_html=True)
            m1, m2, m3 = st.columns(3)
            with m1: bf = st.checkbox("Luxury Breakfast (+100 EGP / Night)")
            with m2: lu = st.checkbox("Executive Lunch (+200 EGP / Night)")
            with m3: dn = st.checkbox("Gourmet Dinner (+250 EGP / Night)")
            
            if st.form_submit_button("Confirm Room Reservation", type="primary"):
                try:
                    in_date_obj = datetime.strptime(in_date, "%d-%m-%Y")
                    today_obj = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
                    
                    dur = calculate_days(in_date, out_date)
                    
                    if in_date_obj < today_obj:
                        st.error("⚠️ Invalid Date! You cannot book a room in the past.")
                    elif dur <= 0:
                        st.error("⚠️ Invalid Timeline! Please ensure Check-out date succeeds Check-in date.")
                    else:
                        b_cnt = 1 if bf else 0
                        l_cnt = 1 if lu else 0
                        d_cnt = 1 if dn else 0
                        
                        room_obj = next(r for r in rooms_db if r['RoomNum'] == r_select)
                        room_base_price = room_obj['RoomPrice']
                        meal_price_per_night = (b_cnt * 100.0) + (l_cnt * 200.0) + (d_cnt * 250.0)
                        total_calculated_price = dur * (room_base_price + meal_price_per_night)
                        
                        new_id = (res_db[-1]['ResID'] + 1) if res_db else 1
                        res_db.append({
                            "ResID": new_id, "GuestID": guest['id'], "RoomNum": r_select,
                            "CheckIn": in_date, "CheckOut": out_date, "Duration": dur,
                            "Breakfast": b_cnt, "Lunch": l_cnt, "Dinner": d_cnt
                        })
                        for r in rooms_db:
                            if r['RoomNum'] == r_select: r['RoomStatus'] = "Booked (Unavailable)"
                        
                        save_reservations(res_db)
                        save_rooms(rooms_db)
                        
                        st.session_state.booking_success_msg = f"""
                        <div class='done-banner'>
                            <h2 style='color: #22C55E; margin:0;'>🎉 DONE! Room Booked Successfully!</h2>
                            <p style='color: white; font-size: 18px; margin: 10px 0 0 0;'>
                                Room <b>#{r_select}</b> is yours for <b>{dur} nights</b>. <br>
                                <span style='font-size:22px; color:#00BFFF;'><b>Total Price: {total_calculated_price} EGP</b></span>
                            </p>
                        </div>
                        """
                        st.rerun()
                except ValueError:
                    st.error("⚠️ Invalid Date Format! Please use DD-MM-YYYY.")
                    
        st.write("Current Room Inventory Status:")
        st.dataframe(pd.DataFrame(rooms_db), use_container_width=True, hide_index=True)

    with gt2:
        st.markdown("<h3 style='color:#00BFFF;'>📋 Complete Reservation History</h3>", unsafe_allow_html=True)
        my_res = [r for r in res_db if r['GuestID'] == guest['id']]
        my_events = [e for e in events_db if e['GuestID'] == guest['id']]
        
        if not my_res and not my_events:
            st.warning("You currently have no active room reservations or event bookings.")

        if my_res:
            st.markdown("🛏️ Your Room Stays")
            for r in my_res:
                room_info = next((rm for rm in rooms_db if rm['RoomNum'] == r['RoomNum']), {"RoomPrice": 0.0, "RoomType": "N/A"})
                base_p = room_info['RoomPrice']
                meal_cost = (r['Breakfast'] * 100.0) + (r['Lunch'] * 200.0) + (r['Dinner'] * 250.0)
                total_r_cost = r['Duration'] * (base_p + meal_cost)
                
                st.markdown(f"""
                <div style='background: rgba(255,255,255,0.03); border: 1px solid rgba(0, 191, 255, 0.3); padding: 15px; border-radius: 10px; margin-bottom: 10px;'>
                    <h5 style='color: #00BFFF; margin: 0;'>Booking ID: #{r['ResID']} — Room {r['RoomNum']} ({room_info['RoomType']})</h5>
                    <p style='margin: 5px 0 0 0; color: #CBD5E1;'>
                        📅 <b>Duration:</b> {r['Duration']} Nights ({r['CheckIn']} to {r['CheckOut']}) <br>
                        💸 <b>Room Price/Night:</b> {base_p} EGP | 🍔 <b>Meals/Night:</b> {meal_cost} EGP <br>
                        💰 <span style='color:#22C55E; font-weight:bold;'>Total Stay Price: {total_r_cost} EGP</span>
                    </p>
                </div>
                """, unsafe_allow_html=True)
            
            with st.form("cancel_res"):
                cancel_id = st.selectbox("Select Stay ID to Void/Cancel", [r['ResID'] for r in my_res])
                if st.form_submit_button("Cancel Selection"):
                    room_to_free = next(r['RoomNum'] for r in my_res if r['ResID'] == cancel_id)
                    
                    res_db[:] = [r for r in res_db if r['ResID'] != cancel_id]
                    for r in rooms_db:
                        if r['RoomNum'] == room_to_free: r['RoomStatus'] = "Available"
                    
                    save_reservations(res_db)
                    save_rooms(rooms_db)
                    st.success(" Room Stay Voided. Cancelled successfully.")
                    st.rerun()

        if my_events:
            st.markdown("<br>#### 🎉 Your Scheduled Events", unsafe_allow_html=True)
            for e in my_events:
                st.markdown(f"""
                <div style='background: rgba(255,255,255,0.03); border: 1px solid rgba(168, 85, 247, 0.3); padding: 15px; border-radius: 10px; margin-bottom: 10px;'>
                    <h5 style='color: #A855F7; margin: 0;'>Event ID: #{e['EventID']} — {e['Type']} Gala</h5>
                    <p style='margin: 5px 0 0 0; color: #CBD5E1;'>
                        📅 <b>Event Date:</b> {e['Date']} <br>
                        🎤 <b>Entertainment Option:</b> {e['Singer']} <br>
                        💰 <span style='color:#22C55E; font-weight:bold;'>Total Event Price: {e['Price']} EGP</span>
                    </p>
                </div>
                """, unsafe_allow_html=True)
                
            with st.form("cancel_event"):
                c_eid = st.selectbox("Select Event ID to Cancel", [e['EventID'] for e in my_events])
                if st.form_submit_button("Cancel Event"):
                    events_db[:] = [e for e in events_db if e['EventID'] != c_eid]
                    save_events(events_db)
                    st.success(" Event Cancelled Successfully.")
                    st.rerun()

    with gt3:
        st.subheader("Plan & Book a Grand Hall Event")
        with st.form("book_event"):
            ev_type = st.selectbox("Event Type Category", ["Wedding", "Engagement", "Birthday", "Party"])
            ev_singer = st.selectbox("Entertainment Add-on (Only applies to Wedding/Engagement)", ["Without Singer", "With Singer"])
            
            event_default_date = (datetime.now() + timedelta(days=7)).strftime("%d-%m-%Y")
            ev_date = st.text_input("Scheduled Date (DD-MM-YYYY)", value=event_default_date)
            
            if st.form_submit_button("Book Hall & Event", type="primary"):
                try:
                    ev_date_obj = datetime.strptime(ev_date, "%d-%m-%Y")
                    today_obj = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
                    
                    if ev_date_obj < today_obj:
                        st.error("⚠️ Invalid Date! You cannot book an event in the past.")
                    else:
                        price = 0.0
                        singer_val = "N/A"
                        if ev_type in ["Wedding", "Engagement"]:
                            singer_val = ev_singer
                            if ev_type == "Wedding": price = 50000.0 if ev_singer == "With Singer" else 30000.0
                            else: price = 30000.0 if ev_singer == "With Singer" else 15000.0
                        elif ev_type == "Birthday": price = 500.0
                        elif ev_type == "Party": price = 1000.0
                        
                        new_eid = (events_db[-1]['EventID'] + 1) if events_db else 1
                        events_db.append({
                            "EventID": new_eid, "GuestID": guest['id'], "Type": ev_type,
                            "Singer": singer_val, "Date": ev_date, "Price": price
                        })
                        save_events(events_db)
                        
                        st.session_state.booking_success_msg = f"""
                        <div class='done-banner' style='background: linear-gradient(90deg, #3B0764 0%, #581C87 100%) !important; border-color:#A855F7 !important;'>
                            <h2 style='color: #C084FC; margin:0;'>🎉 DONE! Event Hall Secured!</h2>
                            <p style='color: white; font-size: 18px; margin: 10px 0 0 0;'>
                                Your <b>{ev_type}</b> is booked for <b>{ev_date}</b>. <br>
                                <span style='font-size:22px; color:#F472B6;'><b>Total Event Fee: {price} EGP</b></span>
                            </p>
                        </div>
                        """
                        st.rerun()
                except ValueError:
                    st.error("⚠️ Invalid Date Format! Please use DD-MM-YYYY.")

    with gt4:
        st.subheader("Order Amenities & Hospitality Services")
        
        def add_charge(amount, name):
            run_backend_command(["BOOK", str(guest['id']), str(amount)])
            
            guest['extraCharges'] += amount
            for u in users_db:
                if u['id'] == guest['id']: u['extraCharges'] = guest['extraCharges']
            save_users(users_db)
            
            st.session_state.booking_success_msg = f"""
            <div class='done-banner' style='background: linear-gradient(90deg, #1E3A8A 0%, #172554 100%) !important; border-color:#3B82F6 !important;'>
                <h3 style='color: #60A5FA; margin:0;'>🎉 DONE! Service Requested</h3>
                <p style='color: white; font-size: 16px; margin: 5px 0 0 0;'>
                    <b>{name}</b> has been ordered successfully. <br>
                    <span style='font-size:18px; color:#38BDF8;'><b>Charged: {amount} EGP</b></span>
                </p>
            </div>
            """
            st.rerun()

        sc1, sc2, sc3 = st.columns(3)
        with sc1:
            st.markdown("<p style='color:#00BFFF; font-weight:bold;'>💆 Spa & Revitalize</p>", unsafe_allow_html=True)
            if st.button("Massage Session (500 EGP)", use_container_width=True): add_charge(500.0, "Massage Session")
            if st.button("Gym Full-Day Pass (150 EGP)", use_container_width=True): add_charge(150.0, "Gym Full-Day Pass")
            if st.button("Facial Therapy (300 EGP)", use_container_width=True): add_charge(300.0, "Facial Therapy")
            if st.button("Pedicure Care (200 EGP)", use_container_width=True): add_charge(200.0, "Pedicure Care")
            if st.button("Manicure Care (200 EGP)", use_container_width=True): add_charge(200.0, "Manicure Care")
            
        with sc2:
            st.markdown("<p style='color:#00BFFF; font-weight:bold;'>🍽️ Express Room Service</p>", unsafe_allow_html=True)
            if st.button("Angus Beef Burger (150 EGP)", use_container_width=True): add_charge(150.0, "Angus Beef Burger")
            if st.button("Stone-Baked Pizza (200 EGP)", use_container_width=True): add_charge(200.0, "Stone-Baked Pizza")
            if st.button("Italian Truffle Pasta (180 EGP)", use_container_width=True): add_charge(180.0, "Italian Truffle Pasta")
            st.markdown("---")
            with st.form("laundry"):
                l_items = st.number_input("Valet Laundry Quantity", min_value=1, value=1)
                if st.form_submit_button("Order Laundry (50 EGP/item)", use_container_width=True): 
                    add_charge(l_items * 50.0, f"Laundry service ({l_items} items)")
            with st.form("ironing"):
                i_items = st.number_input("Steam Ironing Quantity", min_value=1, value=1)
                if st.form_submit_button("Order Ironing (30 EGP/item)", use_container_width=True): 
                    add_charge(i_items * 30.0, f"Steam Ironing ({i_items} items)")

        with sc3:
            st.markdown("<p style='color:#00BFFF; font-weight:bold;'>🩺 Concierge & Medical</p>", unsafe_allow_html=True)
            if st.button("Private Doctor Consultation (1000 EGP)", use_container_width=True): add_charge(1000.0, "Doctor Consultation")
            if st.button("First Aid Assistance (Free)", use_container_width=True): add_charge(0.0, "First Aid Support")

    with gt5:
        st.subheader("🧾 Comprehensive Checkout Statement")
    
        total_bill = guest['extraCharges']
        breakdown_data = [{"Category": "Spa, Room Service & Extras", "Item Details": "Aggregated Requests via Server", "Amount (EGP)": guest['extraCharges']}]
        
        my_res = [r for r in res_db if r['GuestID'] == guest['id']]
        for res in my_res:
            room_info = next((rm for rm in rooms_db if rm['RoomNum'] == res['RoomNum']), {"RoomPrice": 0.0, "RoomType": "Room"})
            room_price = room_info['RoomPrice']
            meals = (res['Breakfast'] * 100.0) + (res['Lunch'] * 200.0) + (res['Dinner'] * 250.0)
            subtotal = res['Duration'] * (room_price + meals)
            total_bill += subtotal
            breakdown_data.append({
                "Category": f"Room Booking #{res['RoomNum']}",
                "Item Details": f"{res['Duration']} Nights (Base: {room_price} + Meals: {meals})",
                "Amount (EGP)": subtotal
            })
            
        my_events = [e for e in events_db if e['GuestID'] == guest['id']]
        for ev in my_events:
            total_bill += ev['Price']
            breakdown_data.append({
                "Category": f"Event ID #{ev['EventID']}",
                "Item Details": f"{ev['Type']} Gala on {ev['Date']}",
                "Amount (EGP)": ev['Price']
            })
            
        st.dataframe(pd.DataFrame(breakdown_data), use_container_width=True, hide_index=True)
        st.markdown(f"<div style='background:rgba(0,191,255,0.1); border-left: 5px solid #00BFFF; padding:15px; border-radius:4px;'><h2 style='margin:0; color:white;'>Total Net Outstanding: <span style='color:#22C55E;'>{total_bill} EGP</span></h2></div>", unsafe_allow_html=True)